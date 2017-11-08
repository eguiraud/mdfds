#include <TDummyDecoder.hxx>
#include <TMDFDataSource.hxx>
#include <gtest/gtest.h>

TEST(MDFDS, DummyDecoder)
{
   TMDFDataSource<TDummyDecoder> ds({});
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}