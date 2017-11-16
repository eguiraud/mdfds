#include <TDummyDecoder.hxx>
#include <TMDFDataSource.hxx>
#include <THltVertexReports.hxx>
#include <THltVertexReportsDecoder.hxx>

#include <gtest/gtest.h>

#include <random>
#include <vector>
using namespace ROOT::Experimental;

const auto fname = "2krecords.raw";

TEST(MDFDS, DummyDecoder)
{
   // file does not have to exist
   TMDFDataSource<TDummyDecoder> ds({fname});
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
   TMDFDataSource<TDummyDecoder> ds({fname});
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
   TMDFDataSource<TDummyDecoder> ds({fname});
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
   auto tdf = MakeMDFDataFrame({fname});
   auto tdf2 = MakeMDFDataFrame<TDummyDecoder>({fname});
}

void ReadHltVerticesImpl()
{
   // get a dataframe
   auto tdf_ = MakeMDFDataFrame<THltVertexReportsDecoder>({fname});

   // define functions that extract x,y,z from a vertex report
   auto getX = [](THltVertexReports &pv) { return std::move(pv.x); };
   auto getY = [](THltVertexReports &pv) { return std::move(pv.y); };
   auto getZ = [](THltVertexReports &pv) { return std::move(pv.z); };

   // define x,y,z colum in the dataframe
   auto tdf = tdf_.Define("x", getX, {"HltVertexReports"})
                 .Define("y", getY, {"HltVertexReports"})
                 .Define("z", getZ, {"HltVertexReports"});

   // produce histograms
   TDF::TH3DModel model("VerticesXYZ", "VerticesXYZ", 50, 0.7, 0.94, 50, -0.3, 0.1, 100, -100, 100);
   auto verticesHist = tdf.Histo3D(model, "x", "y", "z");
   auto nHist = tdf.Define("n", [](const std::vector<float> &x) { return x.size(); }, {"x"}).Histo1D("n");

   // save x,y,z in a TTree
   tdf.Snapshot("tree", "output.root", {"x", "y", "z"});

   // save histograms to file
   TFile f("output.root", "UPDATE");
   verticesHist->SetDirectory(&f);
   nHist->SetTitle("n vertices");
   nHist->SetName("n vertices");
   nHist->SetDirectory(&f);
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
