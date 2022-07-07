#include <gtest/gtest.h>
#define STABLE
#include <range.hpp>

TEST(test_test, passes)
{
    EXPECT_FALSE(false);
}

TEST(test_test, fails)
{
    EXPECT_FALSE(true);
}
using namespace ranges;

TEST(unstable, no_step)
{
    for (int i{}; auto e : in_range(0, 10))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i++;
    }
}
TEST(unstable, step)
{
    for (int i{}; auto e : in_range(0, 10, 1))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i++;
    }
}

TEST(unstable, reversed)
{
    for (int i{9}; auto e : reversed_in_range(10, 0))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i--;
    }
}
TEST(unstable, reversed_step)
{

    for (int i{9}; auto e : reversed_in_range(0, 10, 1))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i--;
    }
}
   
#ifdef STABLE
TEST(stable, no_step_problem_case)
{
    for (int i{}; auto e : in_range(0, 10, stable{}))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i++;
    }
}
TEST(stable, step_problem_case)
{
    for (int i{}; auto e : in_range(0, 10, 1, stable{}))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i++;
    }
}

TEST(stable, reversed_problem_case)
{
    for (int i{9}; auto e : reversed_in_range(10, 0, stable{}))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i--;
    }
}
TEST(stable, reversed_step_problem_case)
{

    for (int i{9}; auto e : reversed_in_range(0, 10, 1, stable{}))
    {
        ASSERT_TRUE(i < 10);
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(e == i);
        i--;
    }
}
#endif //STABLE