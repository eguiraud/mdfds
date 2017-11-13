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

TEST(MDFDS, GetEntryRanges)
{
   TMDFDataSource<> ds({"small.raw"});
   ds.SetNSlots(1u);
   const auto ranges = ds.GetEntryRanges();
   EXPECT_EQ(ranges.size(), 1u);
   EXPECT_EQ(ranges[0].first, 0u);
   EXPECT_EQ(ranges[0].second, 10u); // small.raw contains 10 records
}

TEST(MDFDS, GetEntryRangesMT)
{
   TMDFDataSource<> ds({"small.raw"});
   ds.SetNSlots(4u);
   const auto ranges = ds.GetEntryRanges();
   EXPECT_EQ(ranges.size(), 4u);
   const std::vector<ULong64_t> expected_boundaries = {0u, 2u, 4u, 6u, 10u};
   for (int i = 0u; i < 4u; ++i) {
      EXPECT_EQ(ranges[i].first, expected_boundaries[i]);
      EXPECT_EQ(ranges[i].second, expected_boundaries[i + 1]);
   }
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
