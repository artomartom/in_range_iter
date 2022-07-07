#include <gtest/gtest.h>
#define STABLE
#include <range.hpp>

TEST(test_test, passest1)
{
    EXPECT_FALSE(false);
}
using namespace ranges;

TEST(unstable, t1)
{
    for (int i{}; auto e : in_range(0, 10))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i++;
    }
}
TEST(unstable_step, t1)
{
    for (int i{}; auto e : in_range(0, 10, 1))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i++;
    }
}
TEST(unstable_reversed, t1)
{
    for (int i{9}; auto e : reversed_in_range(10, 0))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i--;
    }
}
TEST(unstable_step_reversed, t1)
{
    for (int i{9}; auto e : reversed_in_range(10, 0))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i--;
    }
}

#ifdef STABLE

TEST(stable, t1)
{
    for (int i{}; auto e : in_range(0, 10))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i++;
    }
}
TEST(stable_step, t1)
{
    for (int i{}; auto e : in_range(0, 10, 1))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i++;
    }
}
TEST(stable_reversed, t1)
{
    for (int i{9}; auto e : reversed_in_range(10, 0))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i--;
    }
}
TEST(stable_step_reversed, t1)
{
    for (int i{9}; auto e : reversed_in_range(10, 0))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i--;
    }
}

#endif // STABLE