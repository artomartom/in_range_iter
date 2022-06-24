#include <gtest/gtest.h>
#include <iostream>

TEST(diFF,passes)
{
    EXPECT_FALSE(false)   ;
}

TEST(diFF,fails)
{
    EXPECT_FALSE(true)   ;
}