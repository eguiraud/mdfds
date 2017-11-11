#include <TDummyDecoder.hxx>
#include <TMDFDataSource.hxx>

#include <TSystem.h>

#include <gtest/gtest.h>

TEST(MDFDS, DummyDecoder)
{
   // file does not have to exist
   TMDFDataSource<TDummyDecoder> ds({"small.raw"});
}

TEST(MDFDS, DummyDecoderTDF)
{
   auto tdf = MakeMDFDataFrame({"small.raw"});
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
