#include <TDummyDecoder.hxx>
#include <TMDFDataSource.hxx>
#include <THltVertexReportsDecoder.hxx>

#include <gtest/gtest.h>

#include <random>
#include <vector>

TEST(MDFDS, DummyDecoder)
{
   // file does not have to exist
   TMDFDataSource<TDummyDecoder> ds({"small.raw"});
}

TEST(MDFDS, GetEntryRanges)
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

TEST(MDFTDF, MakeMDFDataFrame)
{
   auto tdf = MakeMDFDataFrame({"small.raw"});
   auto tdf2 = MakeMDFDataFrame<TDummyDecoder>({"small.raw"});
}

void ReadHltVerticesImpl()
{
   auto tdf = MakeMDFDataFrame<THltVertexReportsDecoder>({"small.raw"});
   auto d = tdf.Define("x",
                       [](const THltVertexReports &pv) {
                          auto x = std::move(pv.x);
                          return x;
                       },
                       {"HltVertexReports"})
               .Define("y",
                       [](const THltVertexReports &pv) {
                          auto y = std::move(pv.y);
                          return y;
                       },
                       {"HltVertexReports"})
               .Define("z",
                       [](const THltVertexReports &pv) {
                          auto z = std::move(pv.z);
                          return z;
                       },
                       {"HltVertexReports"});
   auto h = d.Histo3D<std::vector<float>, std::vector<float>, std::vector<float>>(
      {"HltVertexReportsXYZ", "HltVertexReportsXYZ", 50, 0.7, 0.94, 50, -0.3, 0.1, 100, -100, 100}, "x", "y", "z");
   TFile f("output.root", "RECREATE");
   h->SetDirectory(&f);
   f.Write();
}

TEST(MDFTDF, ReadHltVertices)
{
   ReadHltVerticesImpl();
}


TEST(MDFTDF, ReadHltVerticesMT)
{
   ROOT::EnableImplicitMT();
   ReadHltVerticesImpl();
   ROOT::DisableImplicitMT();
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
