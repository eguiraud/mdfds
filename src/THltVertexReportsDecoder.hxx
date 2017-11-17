#ifndef THLTVERTEXREPORTSDECODER
#define THLTVERTEXREPORTSDECODER

#include "TBankDecoder.hxx"

#include <ROOT/RArrayView.hxx>

/// \brief Implements the decoding of the HltVertexReports bank
/// With this class, all the useful information from the HltVertexReports bank is extracted.
class THltVertexReportsDecoder final : public TBankDecoder {
public:
   ~THltVertexReportsDecoder() {}
   std::string GetName() const final { return "HltVertexReports"; };     // TODO: shouldn't this be a const ref?
   std::string GetTypeName() const final { return "THltVertexReports"; }; // TODO: shouldn't this be a const ref?
   const std::type_info &GetTypeInfo() const final;
   EBankType GetID() const;
   void Decode(std::array_view<char> bank, void *destination) const final;
   void *Allocate() const final;
   void Deallocate(void *obj) const final;
};

#endif
