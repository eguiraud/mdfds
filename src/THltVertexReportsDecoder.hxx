#ifndef THLTVERTEXREPORTSDECODER
#define THLTVERTEXREPORTSDECODER

#include "TBankDecoder.hxx"

#include <ROOT/RArrayView.hxx>

#include <vector>

/// \brief The C++ representation of the HltVertexReports bank
/// This struct is a SOA which represents the primary vertices of an event.
struct THltVertexReports {
   std::vector<float> x;
   std::vector<float> y;
   std::vector<float> z;
   std::vector<float> chi2;
   std::vector<unsigned int> ndof;
   std::vector<float> cov_00;
   std::vector<float> cov_11;
   std::vector<float> cov_22;
   std::vector<float> cov_01;
   std::vector<float> cov_02;
   std::vector<float> cov_12;
};

/// \brief Implements the decoding of the HltVertexReports bank
/// With this class, all the useful information from the HltVertexReports bank is extracted.
class THltVertexReportsDecoder final : public TBankDecoder {
public:
   ~THltVertexReportsDecoder() {}
   std::string GetName() const final { return "HltVertexReports"; };     // TODO: shouldn't this be a const ref?
   std::string GetTypeName() const final { return "HltVertexReports"; }; // TODO: shouldn't this be a const ref?
   const std::type_info &GetTypeInfo() const final;
   EBankType GetID() const;
   void Decode(std::array_view<char> bank, void *destination) const final;
   void *Allocate() const final;
   void Deallocate(void *obj) const final;
};

#endif
