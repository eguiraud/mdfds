#ifndef TDUMMYDECODER
#define TDUMMYDECODER

#include "TBankDecoder.hxx"

class TDummyDecoder : public TBankDecoder {
public:
   std::string GetName() const final { return "dummy"; }
   std::string GetTypeName() const final { return "int"; }
   const std::type_info &GetTypeInfo() const { return typeid(int); }
   int GetID() const final { return 0; } // hi-jacking a real bank ID for our purposes
   void Decode(const char *, void *destination) const final { *static_cast<int *>(destination) = 42; }
   void *Allocate() const final;
   void Deallocate(void *obj) const final;
};

#endif