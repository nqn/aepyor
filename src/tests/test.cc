#include <iostream>

#include "gtest/gtest.h"

TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
}

TEST(sample_test_case, sample_test_2)
{
    EXPECT_EQ(1, 0);
}
