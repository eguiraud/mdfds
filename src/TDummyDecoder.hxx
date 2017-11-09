#ifndef TDUMMYDECODER
#define TDUMMYDECODER

#include "TBankDecoder.hxx"

class TDummyDecoder : public TBankDecoder {
public:
   std::string GetName() const { return "dummy"; }
   std::string GetTypeName() const { return "int"; }
   int GetID() const { return 123456; }
   void Decode(const char *, void *destination) const { *static_cast<int*>(destination) = 42; }
   std::vector<void *> Allocate(unsigned int N, const std::type_info &expectedType) const;
   void Deallocate(const std::vector<void *> &objs) const;
};

#endif