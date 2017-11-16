#include <BankTypes.h>
#include <THltVertexReports.hxx>
#include <THltVertexReportsDecoder.hxx>
#include <TRecordReader.hxx>

#include <gtest/gtest.h>
#include <iostream>
#include <iomanip>

const auto fname = "small.raw";

struct with_width {
   int w;
   with_width(int w) : w(w) {}
};
auto operator<<(std::ostream &os, const with_width &w) -> decltype(os << std::setw(0) << std::left)
{
   return os << std::setw(w.w) << std::left;
}

TEST(THltVertexReportsDecoder, DecodeHltVertexReportsBanks)
{
   THltVertexReportsDecoder pvDecoder;
   TRecordReader r(fname);
   for (auto recordn = 0u; r.NextRecord(); ++recordn) {
      for (auto bankn = 0u; r.NextBank(); ++bankn) {
         auto bankHeader = r.GetBankHeader();
         // We now test the vertices
         if (bankHeader.type != EBankType::HltVertexReports) {
            continue;
         }

         std::cout << "record " << with_width(7) << recordn << "bank " << with_width(7) << bankn
                   << " pos: " << with_width(10) << r.GetBankPosition() << " size: " << with_width(7) << bankHeader.size
                   << " type: " << with_width(7) << bankHeader.type << " version: " << with_width(7)
                   << bankHeader.version << '\n';

         auto bankBody = r.GetBankBody();
         auto pvsPtr = (THltVertexReports *)pvDecoder.Allocate();
         auto &pvs = *pvsPtr;
         pvDecoder.Decode(bankBody, (void *)pvsPtr);
         auto nPvs = pvs.x.size();
         std::cout << "Found " << nPvs << " primary vertices:" << std::endl;
         for (size_t i = 0; i < nPvs; ++i) {
            std::cout << " - Vtx " << i << ": "
                      << "x = " << pvs.x[i] << " "
                      << "y = " << pvs.y[i] << " "
                      << "z = " << pvs.z[i] << " "
                      << "chi2 = " << pvs.chi2[i] << " "
                      << "ndof = " << pvs.ndof[i] << " "
                      << "cov_00 = " << pvs.cov_00[i] << " "
                      << "cov_11 = " << pvs.cov_11[i] << " "
                      << "cov_22 = " << pvs.cov_22[i] << " "
                      << "cov_01 = " << pvs.cov_01[i] << " "
                      << "cov_02 = " << pvs.cov_02[i] << " "
                      << "cov_12 = " << pvs.cov_12[i] << std::endl;
         }

         pvDecoder.Deallocate(pvsPtr);
      }
   }
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
