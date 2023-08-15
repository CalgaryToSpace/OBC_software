#include <gtest/gtest.h>
#include "../Example2.hpp"

TEST(ExampleTest2, FirstTest) {
    EXPECT_EQ(2,2);
}
TEST(ExampleTest2, SecondTest) {
    EXPECT_EQ(ret5(), 5);
}