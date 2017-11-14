#ifndef THLTVERTEXREPORTSDECODER
#define THLTVERTEXREPORTSDECODER

#include "TBankDecoder.hxx"

/// \brief Implements the decoding of the HltVertexReports bank
/// With this class, all the useful information from the HltVertexReports bank is extracted.
class THltVertexReportsDecoder final : public TBankDecoder {
public:
   ~THltVertexReportsDecoder() {}
   std::string GetName() const { return "HltVertexReports"; };     // TODO: shouldn't this be a const ref?
   std::string GetTypeName() const { return "HltVertexReports"; }; // TODO: shouldn't this be a const ref?
   const std::type_info &GetTypeInfo() const;
   EBankType GetID() const;
   void Decode(const std::vector<char> &bank, void *destination) const;
   void *Allocate() const;
   void Deallocate(void *obj) const;
};

#endif
