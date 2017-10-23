#include "gtest/gtest.h"

TEST(MDFDS, NoOp) {
   int a = 3;
   int b = a;
   EXPECT_EQ(a,b);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}