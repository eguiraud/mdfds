#ifndef TMDFDATASOURCE
#define TMDFDATASOURCE

#include "TBankDecoder.hxx"
#include "TRecordReader.hxx"

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
   std::vector<TBankDecoder *> fDecoderPtrs; // TODO const?
   std::vector<std::string> fDecoderNames; // TODO const?
   std::vector<std::string> fFileNames;
   std::vector<RecordReader> fRecordReaders; ///< per-slot file buffers, used to traverse and read the input files

public:
   TMDFDataSource(const std::vector<std::string> &fileNames)
      : fDecoders(), fDecoderPtrs(GetDecoderAddresses(DecoderInd_t())), fDecoderNames(GetDecoderNames(DecoderInd_t())),
        fFileNames(fileNames) {}

   void SetNSlots(unsigned int nSlots) { fNSlots = nSlots; }

   const std::vector<std::string> &GetColumnNames() const { return fDecoderNames; }

   bool HasColumn(std::string_view col) const
   {
      return std::find(fDecoderNames.begin(), fDecoderNames.end(), col) != fDecoderNames.end();
   }

   std::string GetTypeName(std::string_view col) const
   {
      const auto ind = std::distance(fDecoderNames.begin(), std::find(fDecoderNames.begin(), fDecoderNames.end(), col));
      return fDecoderPtrs[ind]->GetName();
   }

   std::vector<std::pair<ULong64_t, ULong64_t>> GetEntryRanges() { return {}; /* TODO */ }

   void SetEntry(unsigned int slot, ULong64_t entry) { /*TODO*/ }

   // TODO refactor following methods, make private
   bool NextRecord(unsigned int slot = 0u)
   {
      fRecordReaders[slot].NextRecord();
   }

   RecordReader &GetRecordReader(unsigned int slot = 0u)
   {
      return fRecordReaders[0];
   }

private:
   /// Return a type-erased vector of pointers to pointers to column values - one per slot
   std::vector<void *> GetColumnReadersImpl(std::string_view name, const std::type_info &) { return {}; /*TODO*/ }

   template <int ...S>
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
   return ROOT::Experimental::TDataFrame(
      std::unique_ptr<TMDFDataSource<Decoders...>>(new TMDFDataSource<Decoders...>(fileNames)));
}

#endif
