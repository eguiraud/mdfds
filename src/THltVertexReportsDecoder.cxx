#include "THltVertexReportsDecoder.hxx"
#include "BankTypes.h"

#include <iostream>
#include <sstream>

const std::type_info &THltVertexReportsDecoder::GetTypeInfo() const
{
   return typeid(THltVertexReports);
}

EBankType THltVertexReportsDecoder::GetID() const
{
   return EBankType::HltVertexReports;
}

struct TPVInfo {
   float x;
   float y;
   float z;
   float chi2;
   unsigned int ndof;
   float cov_00;
   float cov_11;
   float cov_22;
   float cov_01;
   float cov_02;
   float cov_12;
};

// The structure of the bank can be inferred from
// http://lhcb-doxygen.web.cern.ch/lhcb-doxygen/moore/latest/d0/da9/class_hlt_vertex_reports_decoder.html
// (thanks to Rosen Matev for the help in understanding it!)
// - (uint32) the number of "selections" (there can be different types of PVs, but normally this should be 1)
// - for each selection:
//   - (uint16) number of PVs
//   - (uint16) "selection" ID
//   - for each PV:
//      - (float) x, (float) y, (float) z,  (float) chi2,  (uint32) ndof,
//        (float) cov[0][0], (float) cov[1][1], (float) cov[2][2], (float) cov[0][1], (float) cov[0][2], (float)
//        cov[1][2]
// For simplicity, we'll consider only vertices with selection equal to 1.
// An example record, in chars, looks like this one:
//
// 10000000 00000000 00000000 00000000         selections

// 10000000 00000000 11900000 39000000         nvtx / selID

// 4294967213 51000000 67000000 63000000       x
// 93000000 35000000 4294967189 4294967229     y
// 4294967175 4294967276 4294967173 4294967232 z

// 44000000 4294967276 10000000 66000000       chi2
// 12300000 00000000 00000000 00000000         ndof

// 11500000 12700000 4294967202 56000000       cov_00
// 72000000 4294967173 4294967182 56000000     cov_11
// 4294967251 4294967203 18000000 59000000     cov_22
// 11700000 86000000 64000000 53000000         cov_01
// 77000000 90000000 22000000 4294967225       cov_02
// 10500000 18000000 88000000 4294967223       cov_12

void THltVertexReportsDecoder::Decode(const std::vector<char> &bank, void *destination) const
{
   auto &vReps = *reinterpret_cast<THltVertexReports *>(destination);
   vReps.ndof.clear();
   for (auto &v : {&vReps.x, &vReps.y, &vReps.z, &vReps.chi2, &vReps.cov_00, &vReps.cov_11, &vReps.cov_22, &vReps.cov_01,
                  &vReps.cov_02, &vReps.cov_12}) {
      v->clear();
   }

   // Read the selection type
   auto &nSel = pun_to<unsigned int>(bank[0]);
   if (1U != nSel) {
      std::cerr << "The number of HltVertexReports selections for this entry is not 1. Returning zero vertices."
                << std::endl;
      return;
   }

   auto &nPVs = pun_to<unsigned short>(bank[4]);
   if (0 == nPVs) {
      return;
   }

   vReps.ndof.reserve(nPVs);
   for (auto v : {&vReps.x, &vReps.y, &vReps.z, &vReps.chi2, &vReps.cov_00, &vReps.cov_11, &vReps.cov_22, &vReps.cov_01,
                  &vReps.cov_02, &vReps.cov_12}) {
      v->reserve(nPVs);
   }

   // Now loop on the PVs
   for (unsigned short i = 0; i < nPVs; ++i) {
      auto offset = 8 + i * 11 * 4; // start of the first x, ith vtx * elements of info per vtx * size of element
      auto &pvInfo = pun_to<TPVInfo>(bank[offset]);
      vReps.x.emplace_back(pvInfo.x);
      vReps.y.emplace_back(pvInfo.y);
      vReps.z.emplace_back(pvInfo.z);
      vReps.chi2.emplace_back(pvInfo.chi2);
      vReps.ndof.emplace_back(pvInfo.ndof);
      vReps.cov_00.emplace_back(pvInfo.cov_00);
      vReps.cov_11.emplace_back(pvInfo.cov_11);
      vReps.cov_22.emplace_back(pvInfo.cov_22);
      vReps.cov_01.emplace_back(pvInfo.cov_01);
      vReps.cov_02.emplace_back(pvInfo.cov_02);
      vReps.cov_12.emplace_back(pvInfo.cov_12);
   }
}

void *THltVertexReportsDecoder::Allocate() const
{
   return new THltVertexReports();
}

void THltVertexReportsDecoder::Deallocate(void *obj) const
{
   delete reinterpret_cast<THltVertexReports *>(obj);
}
