#include <TRecordReader.hxx>
#include <TSystem.h>
#include <gtest/gtest.h>
#include <iostream>

TEST(RecordReader, TraverseRecords)
{
   const auto fname = "small.raw";
   const auto fileExists = !gSystem->AccessPathName(fname); // weird return value convention
   ASSERT_TRUE(fileExists) << "Could not run test: test file not found.";

   TRecordReader r(fname);
   for (auto counter = 0u; r.NextRecord(); ++counter) {
      std::cout << counter << "\t current position: " << r.GetRecordPosition()
                << "\t record size: " << r.GetRecordSize() << '\n';
   }
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
