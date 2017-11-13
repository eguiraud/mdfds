#ifndef TMDFDATASOURCE
#define TMDFDATASOURCE

#include "TBankDecoder.hxx"
#include "TRecordReader.hxx"

#include <ROOT/RMakeUnique.hxx>
#include <ROOT/TDataFrame.hxx>
#include <ROOT/TDataSource.hxx>
#include <ROOT/TDFUtils.hxx> // GenStaticSeq, StaticSeq
#include <tuple>

/// \brief A concrete TDataSource implementation that reads MDF files
template <typename... Decoders>
class TMDFDataSource : public ROOT::Experimental::TDF::TDataSource {
   using DecoderInd_t = ROOT::Internal::TDF::GenStaticSeq_t<sizeof...(Decoders)>;

   unsigned int fNSlots = 0u;
   std::tuple<Decoders...> fDecoders;
   const std::vector<TBankDecoder *> fDecoderPtrs; // TODO const?
   const std::vector<std::string> fDecoderNames;   // TODO const?
   const std::vector<std::string> fFileNames;
   std::vector<TRecordReader> fRecordReaders; ///< Per-slot record readers
   /// Index of the current file being processed in fFileNames
   std::size_t fCurrentFile = std::numeric_limits<std::size_t>::max();
   /// Per-slot pointers to column values. Use as fColumnValues[slot][columnIndex].
   std::vector<std::vector<void *>> fColumnValues;

public:
   explicit TMDFDataSource(const std::vector<std::string> &fileNames)
      : fDecoders(), fDecoderPtrs(GetDecoderAddresses(DecoderInd_t())), fDecoderNames(GetDecoderNames(DecoderInd_t())),
        fFileNames(fileNames)
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
      // TODO: smarter division of records in entry ranges
      // get the next file, count records, return fNSlots different ranges
      fCurrentFile = fCurrentFile == std::numeric_limits<std::size_t>::max() ? 0u : fCurrentFile + 1u;
      if (fCurrentFile >= fFileNames.size())
         return {}; // no more files to process

      TRecordReader r(fFileNames[fCurrentFile]);
      auto nRecords = 0u;
      while (r.NextRecord())
         ++nRecords;

      const auto chunkSize = nRecords / fNSlots;
      const auto remainder = nRecords % fNSlots;
      auto start = 0ul;
      auto end = 0ul;

      std::vector<std::pair<ULong64_t, ULong64_t>> entryRanges;
      for (auto i = 0u; i < fNSlots; ++i) {
         start = end;
         end += chunkSize;
         entryRanges.emplace_back(start, end);
      }
      entryRanges.back().second += remainder;
      return entryRanges;
   }

   void SetEntry(unsigned int slot, ULong64_t entry) { /*TODO*/}

private:
   /// Return a type-erased vector of pointers to pointers to column values - one per slot
   std::vector<void *> GetColumnReadersImpl(std::string_view name, const std::type_info &)
   {
      std::vector<void *> columnPtrPtrs(fNSlots);
      const auto ind =
         std::distance(fDecoderNames.begin(), std::find(fDecoderNames.begin(), fDecoderNames.end(), name));
      if (ind == fDecoderNames.size()) {
         std::cerr << "warning: could not find \"" << name << "\", no readers returned";
         return {};
      }
      for (auto slot = 0u; slot < fNSlots; ++slot)
         columnPtrPtrs[slot] = &fColumnValues[slot][ind];
      return columnPtrPtrs;
   }

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
};

template <typename... Decoders>
ROOT::Experimental::TDataFrame MakeMDFDataFrame(const std::vector<std::string> &fileNames)
{
   return ROOT::Experimental::TDataFrame(std::make_unique<TMDFDataSource<Decoders...>>(fileNames));
}

#endif
