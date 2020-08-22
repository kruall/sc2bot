#include <gtest/gtest.h>


TEST(SampleTest, Add) {
  EXPECT_EQ(1 + 2, 3);
  EXPECT_EQ(2 + 2, 4);
}

TEST(SampleTest, Mul) {
  EXPECT_EQ(1 * 2, 2);
  EXPECT_EQ(2 * 2, 4);
}
