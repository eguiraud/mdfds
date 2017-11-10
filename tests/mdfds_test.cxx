#include <TDummyDecoder.hxx>
#include <TMDFDataSource.hxx>
#include <TRecordReader.hxx>

#include <TSystem.h>

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

TEST(MDFDS, DISABLED_ReadRecords)
{
   const auto fname = "";
   const auto fileExists = !gSystem->AccessPathName(fname); // weird return value convention
   ASSERT_TRUE(fileExists) << "Could not run test: test file not found.";

   TMDFDataSource<> ds({fname});
   while (ds.NextRecord()) {
      auto &r = ds.GetRecordReader();
      std::cout << "current position: " << r.GetRecordPosition() << std::endl;
   }
}

TEST(MDFDS, GetBank)
{
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}