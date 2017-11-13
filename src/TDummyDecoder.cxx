#include "TDummyDecoder.hxx"

void *TDummyDecoder::Allocate() const
{
   return new int(42);
}

void TDummyDecoder::Deallocate(void *obj) const
{
   delete static_cast<int *>(obj);
}
