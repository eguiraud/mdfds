#ifndef THLTVERTEXREPORTS
#define THLTVERTEXREPORTS

#include <vector>

/// \brief The C++ representation of the HltVertexReports bank
/// This struct is a SOA which represents the primary vertices of an event.
struct THltVertexReports {
   std::vector<float> x;
   std::vector<float> y;
   std::vector<float> z;
   std::vector<float> chi2;
   std::vector<unsigned int> ndof;
   std::vector<float> cov_00;
   std::vector<float> cov_11;
   std::vector<float> cov_22;
   std::vector<float> cov_01;
   std::vector<float> cov_02;
   std::vector<float> cov_12;
};

#endif