#ifndef TMDFDATASOURCE
#define TMDFDATASOURCE

#include "TBankDecoder.hxx"
#include "TRecordReader.hxx"

#include <ROOT/RMakeUnique.hxx>
#include <ROOT/TDataFrame.hxx>
#include <ROOT/TDataSource.hxx>
#include <ROOT/TDFUtils.hxx> // GenStaticSeq, StaticSeq
#include <tuple>
#include <unordered_map>

/// \brief A concrete TDataSource implementation that reads MDF files
template <typename... Decoders>
class TMDFDataSource : public ROOT::Experimental::TDF::TDataSource {
   using DecoderInd_t = ROOT::Internal::TDF::GenStaticSeq_t<sizeof...(Decoders)>;

   unsigned int fNSlots = 0u;
   // TODO check we are using the tuple and not the pointers to decoders in the event loop
   /// Tuple of objects of types inheriting from TBankDecoders.
   std::tuple<Decoders...> fDecoders;
   /// List of pointers to the decoders, with the same ordering as the decoders in fDecoders
   const std::vector<TBankDecoder *> fDecoderPtrs;
   /// List of decoder names (i.e. column names), with the same ordering as the decoders in fDecoders
   const std::vector<std::string> fDecoderNames;
   /// List of decoder ids (i.e. bank type), with same ordering as the decoders in fDecoders
   const std::vector<int> fDecoderIDs;
   /// List of files we will loop over
   const std::vector<std::string> fFileNames;
   /// Index of the current file being processed in fFileNames
   std::size_t fCurrentFile = std::numeric_limits<std::size_t>::max();
   /// The entry number at which new entry ranges should start
   /// Corresponds to the last entry of the previous batch of entry ranges
   ULong64_t fEntryOffset = 0ul;
   /// Per-slot record readers
   std::vector<TRecordReader> fRecordReaders;
   /// Per-slot pointers to column values. Use as fColumnValues[slot][columnIndex].
   std::vector<std::vector<void *>> fColumnValues;
   /// Unordered map entry->file_position for the first entries of each range.
   /// Used by SetEntry to perform jumps between distant records when a TRecordReader must switch entry range.
   std::unordered_map<ULong64_t, TRecordReader::pos_type> fEntryPositions;
   /// Per-slot current entry number
   std::vector<ULong64_t> fCurrentEntries;

public:
   explicit TMDFDataSource(const std::vector<std::string> &fileNames)
      : fDecoders(), fDecoderPtrs(GetDecoderAddresses(DecoderInd_t())), fDecoderNames(GetDecoderNames(DecoderInd_t())),
        fDecoderIDs(GetDecoderIDs(DecoderInd_t())), fFileNames(fileNames)
   {
      if (fFileNames.empty())
         throw std::invalid_argument("empty list of files");
   }

   void SetNSlots(unsigned int nSlots)
   {
      fNSlots = nSlots;

      fRecordReaders.reserve(fNSlots);
      for (auto i = 0u; i < fNSlots; ++i)
         fRecordReaders.emplace_back(fFileNames[0]);

      fColumnValues.resize(fNSlots);
      constexpr auto nColumns = std::tuple_size<decltype(fDecoders)>::value;
      for (auto &colValues : fColumnValues) {
         colValues.resize(nColumns);
         for (auto colInd = 0u; colInd < nColumns; ++colInd)
            colValues[colInd] = fDecoderPtrs[colInd]->Allocate();
      }

      fCurrentEntries.resize(fNSlots, 0ul);
   }

   const std::vector<std::string> &GetColumnNames() const { return fDecoderNames; }

   bool HasColumn(std::string_view col) const
   {
      return std::find(fDecoderNames.begin(), fDecoderNames.end(), col) != fDecoderNames.end();
   }

   std::string GetTypeName(std::string_view col) const
   {
      const auto ind = std::distance(fDecoderNames.begin(), std::find(fDecoderNames.begin(), fDecoderNames.end(), col));
      return fDecoderPtrs[ind]->GetTypeName();
   }

   std::vector<std::pair<ULong64_t, ULong64_t>> GetEntryRanges()
   {
      // Create a new range every ~1GB. Each TDF task will process ~1GB of records (typically only reading parts of it)
      return GetEntryRanges(/*minRangesize=*/1024 * 1024 * 1024);
   }

   std::vector<std::pair<ULong64_t, ULong64_t>> GetEntryRanges(TRecordReader::pos_type minRangeSize)
   {
      // TODO: smarter division of records in entry ranges
      // get the next file, count records, return fNSlots different ranges
      fCurrentFile = fCurrentFile == std::numeric_limits<std::size_t>::max() ? 0u : fCurrentFile + 1u;
      if (fCurrentFile >= fFileNames.size())
         return {}; // no more files to process

      TRecordReader r(fFileNames[fCurrentFile]);
      fEntryPositions.clear();
      fEntryPositions[fEntryOffset] = 0;
      std::vector<std::pair<ULong64_t, ULong64_t>> entryRanges;
      TRecordReader::pos_type rangeStartPos = 0;
      auto recordsInRange = 0u;

      while (r.NextRecord()) {
         const auto recordPos = r.GetRecordPosition();
         if (recordPos - rangeStartPos > minRangeSize) {
            entryRanges.emplace_back(fEntryOffset, fEntryOffset + recordsInRange);
            rangeStartPos = recordPos;
            fEntryOffset += recordsInRange;
            fEntryPositions[fEntryOffset] = rangeStartPos;
            recordsInRange = 0u;
         }
         ++recordsInRange;
      }
      // deal with last records
      if (recordsInRange > 0u) {
         entryRanges.emplace_back(fEntryOffset, fEntryOffset + recordsInRange); // TOCHECK!
         fEntryOffset += recordsInRange;
      }
      return entryRanges;
   }

   void SetEntry(unsigned int slot, ULong64_t entry)
   {
      auto &curEntry = fCurrentEntries[slot];
      auto &recordReader = fRecordReaders[slot];
      if (entry == curEntry + 1) {
         // next entry in range, or first entry of a consecutive range. we can just keep going.
         recordReader.NextRecord();
      } else {
         // start of a new entry range, jump the correct file position
         recordReader.SeekRecordAt(fEntryPositions.at(entry));
      }
      fCurrentEntries[slot] = entry;

      while (recordReader.NextBank())
      {
         const auto bh = recordReader.GetBankHeader();
         const std::size_t bankInd =
            std::distance(fDecoderIDs.begin(), std::find(fDecoderIDs.begin(), fDecoderIDs.end(), bh.type));
         if (bankInd < sizeof...(Decoders)) // we have a decoder for this bank
            fDecoderPtrs[bankInd]->Decode(recordReader.GetBankBody().data(), fColumnValues[slot][bankInd]);
      }
   }

private:
   /// Return a type-erased vector of pointers to pointers to column values - one per slot
   std::vector<void *> GetColumnReadersImpl(std::string_view name, const std::type_info &)
   {
      std::vector<void *> columnPtrPtrs(fNSlots);
      const std::size_t ind =
         std::distance(fDecoderNames.begin(), std::find(fDecoderNames.begin(), fDecoderNames.end(), name));
      if (ind == fDecoderNames.size()) {
         std::cerr << "warning: could not find \"" << name << "\", no readers returned\n";
         return {};
      }
      for (auto slot = 0u; slot < fNSlots; ++slot)
         columnPtrPtrs[slot] = &fColumnValues[slot][ind];
      return columnPtrPtrs;
   }

   // TODO refactor these to avoid code repetition
   template <int... S>
   std::vector<TBankDecoder *> GetDecoderAddresses(ROOT::Internal::TDF::StaticSeq<S...>)
   {
      return {static_cast<TBankDecoder *>(&std::get<S>(fDecoders))...};
   }

   template <int... S>
   std::vector<std::string> GetDecoderNames(ROOT::Internal::TDF::StaticSeq<S...>) const
   {
      return {std::get<S>(fDecoders).GetName()...};
   }

   template <int... S>
   std::vector<int> GetDecoderIDs(ROOT::Internal::TDF::StaticSeq<S...>) const
   {
      return {std::get<S>(fDecoders).GetID()...};
   }
};

template <typename... Decoders>
ROOT::Experimental::TDataFrame MakeMDFDataFrame(const std::vector<std::string> &fileNames)
{
   return ROOT::Experimental::TDataFrame(std::make_unique<TMDFDataSource<Decoders...>>(fileNames));
}

#endif
