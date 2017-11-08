#include "TDummyDecoder.hxx"

std::vector<void *> TDummyDecoder::Allocate(unsigned int N, const std::type_info &expectedType) const
{
   std::vector<void *> v(N, nullptr);
   for (auto &e : v)
      e = new int;
   return v;
}

void TDummyDecoder::Deallocate(const std::vector<void *> &objs) const
{
   for (auto p : objs)
      delete static_cast<int *>(p);
}
