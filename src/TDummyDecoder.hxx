#ifndef TDUMMYDECODER
#define TDUMMYDECODER

#include "TBankDecoder.hxx"

class TDummyDecoder : public TBankDecoder {
public:
   std::string GetName() const final { return "dummy"; }
   std::string GetTypeName() const final { return "int"; }
   const std::type_info &GetTypeInfo() const { return typeid(int); }
   EBankType GetID() const final { return EBankType::LastType; }
   void Decode(const std::vector<char> &, void *destination) const final { *static_cast<int *>(destination) = 42; }
   void *Allocate() const final;
   void Deallocate(void *obj) const final;
};

#endif