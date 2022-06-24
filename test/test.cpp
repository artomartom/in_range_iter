#include <gtest/gtest.h>

TEST(diFF,passes)
{
    EXPECT_FALSE(false)   ;
}

TEST(diFF,fails)
{
    EXPECT_FALSE(true)   ;
}
