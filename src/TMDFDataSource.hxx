#ifndef TMDFDATASOURCE
#define TMDFDATASOURCE

#include "TBankDecoder.hxx"

#include <ROOT/RMakeUnique.hxx>
#include <ROOT/TDataFrame.hxx>
#include <ROOT/TDataSource.hxx>
#include <tuple>

/// \brief a concrete TDataSource implementation that reads MDF files
template <typename... Decoders>
class TMDFDataSource : public ROOT::Experimental::TDF::TDataSource {
   unsigned int fNSlots = 0u;
   std::tuple<Decoders...> fDecoders; // TODO: make sure we do not store references or pointers but concrete values
   std::vector<TBankDecoder *> fDecoderPtrs;
   std::vector<std::string> fDecoderNames;

public:
   TMDFDataSource(const std::vector<std::string> &fileNames, Decoders... decoders);
   void SetNSlots(unsigned int nSlots) { fNSlots = nSlots; }
   const std::vector<std::string> &GetColumnNames() const;
   bool HasColumn(std::string_view) const;
   std::string GetTypeName(std::string_view) const;
   std::vector<std::pair<ULong64_t, ULong64_t>> GetEntryRanges();
   void SetEntry(unsigned int slot, ULong64_t entry);

private:
   /// Return a type-erased vector of pointers to pointers to column values - one per slot
   std::vector<void *> GetColumnReadersImpl(std::string_view name, const std::type_info &);
};

template <typename... Decoders>
ROOT::Experimental::TDataFrame MakeMDFDataFrame(const std::vector<std::string> &fileNames, Decoders... decoders)
{
   return ROOT::Experimental::TDataFrame(
      std::make_unique<TMDFDataSource<Decoders...>>(fileNames, std::forward<Decoders>(decoders)...));
}

#endif
