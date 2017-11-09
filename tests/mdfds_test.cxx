#include <TDummyDecoder.hxx>
#include <TMDFDataSource.hxx>
#include <gtest/gtest.h>

TEST(MDFDS, DummyDecoder)
{
   // file does not have to exist
   TMDFDataSource<TDummyDecoder> ds({"file.raw"});
}

TEST(MDFDS, DummyDecoderTDF)
{
   auto tdf = MakeMDFDataFrame({"file.raw"});
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}