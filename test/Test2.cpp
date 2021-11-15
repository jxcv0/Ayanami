#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(secondtest, alsoBasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("test", "two");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}