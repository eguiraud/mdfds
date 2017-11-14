#include <TDummyDecoder.hxx>
#include <TMDFDataSource.hxx>

#include <TSystem.h>

#include <gtest/gtest.h>

#include <random>
#include <vector>

TEST(MDFDS, DummyDecoder)
{
   // file does not have to exist
   TMDFDataSource<TDummyDecoder> ds({"small.raw"});
}

TEST(MDFDS, DummyDecoderTDF)
{
   auto tdf = MakeMDFDataFrame({"small.raw"});
}

TEST(MDFDS, GetEntryRangesMT)
{
   TMDFDataSource<> ds({"small.raw"});
   const auto ranges = ds.GetEntryRanges(41000);
   EXPECT_EQ(ranges.size(), 4u);
   const std::vector<ULong64_t> expected_boundaries = {0u, 3u, 5u, 8u, 10u};
   for (auto i = 0u; i < 4u; ++i) {
      EXPECT_EQ(ranges[i].first, expected_boundaries[i]);
      EXPECT_EQ(ranges[i].second, expected_boundaries[i + 1]);
   }
}

TEST(MDFDS, GetColumnReadersMT)
{
   TMDFDataSource<TDummyDecoder> ds({"small.raw"});
   ds.SetNSlots(4u);
   const std::vector<int **> readers = ds.GetColumnReaders<int>("dummy");
   EXPECT_EQ(readers.size(), 4u);
   for (auto &r : readers) {
      EXPECT_NE(r, nullptr);
      EXPECT_EQ(**r, 42); // check we can dereference twice without crashing
   }
}

TEST(MDFDS, SetEntry)
{
   TMDFDataSource<TDummyDecoder> ds({"small.raw"});
   ds.SetNSlots(2);
   const auto readers = ds.GetColumnReaders<int>("dummy");

   auto ranges = ds.GetEntryRanges();
   std::random_device rd;
   std::mt19937 g(rd());
   std::shuffle(ranges.begin(), ranges.end(), g);

   while (!ranges.empty()) {
      for (const auto &r : ranges) {
         for (auto entry = r.first; entry < r.second; ++entry) {
            ds.SetEntry(0u, entry);
            for (auto &v : readers)
               EXPECT_EQ(**v, 42);
         }
      }
      ranges = ds.GetEntryRanges();
   }
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
