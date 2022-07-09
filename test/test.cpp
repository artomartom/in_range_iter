#include <gtest/gtest.h>
#define STABLE
#include <chrono>
#include <type_traits>
#include <tuple>
#include <range.hpp>

class MyEnvironment : public ::testing::Environment
{
public:
    virtual ~MyEnvironment() = default;

    // Override this to define how to set up the environment.
    virtual void SetUp()
    {
        using namespace std::chrono;
        auto now = high_resolution_clock::now();
        auto time_milisec = duration_cast<milliseconds>(now.time_since_epoch()).count();
        std::srand(time_milisec);
    }

    // Override this to define how to tear down the environment.
    virtual void TearDown() {}
};

using test_types = std::tuple<
    char,
    short,
    int,
    int8_t,
    int16_t,
    int32_t,
    int64_t,
    long,
    long long,
    unsigned char,
    unsigned short,
    unsigned int,
    unsigned int8_t,
    unsigned int16_t,
    unsigned int32_t,
    unsigned int64_t,
    unsigned long,
    unsigned long long>;

using namespace ranges;
template <typename T>
void basic_assert(T from, T to, T step = 1)
{
    for (T i{}; auto e : in_range<T>(from, to))
    {
        ASSERT_TRUE(i >= from) << i << ">=" << from;
        ASSERT_TRUE(i < to) << i << "<" << to;
        ASSERT_TRUE(e == i) << e << "==" << i;
        i += step;
        e += step - 1;
    }
};
template <typename T>
void assert_with_jumps(T from, T to, T step = 1, T jump_rate = 1)
{

    for (T i{}; auto e : in_range<T>(from, to))
    {
        ASSERT_TRUE(i >= from) << i << ">=" << from;
        ASSERT_TRUE(i < to) << i << "<" << to;
        ASSERT_TRUE(e == i) << e << "==" << i;
        i += step;

        if (i % jump_rate)
        {
            auto r{std::rand() % jump_rate};
            i -= r;
            e -= r;
        };
    }
};
template <typename T>
void test_all()
{
    basic_assert<T>(0, 10, 1);
    basic_assert<T>(0, 10, 2);
    basic_assert<T>(0, 10, 10);
    assert_with_jumps<T>(0, 10, 1, 1);
    assert_with_jumps<T>(3, 10, 1, 5);
    assert_with_jumps<T>(0, 10, 2, 3);
};

TEST(unstable, t1)
{
}

#undef STABLE
#ifdef STABLE

TEST(stable, t1)
{
    EXPECT_FALSE(false);
}
TEST(stable_step, t1)
{
    EXPECT_FALSE(false);
}
TEST(stable_reversed, t1)
{
    EXPECT_FALSE(false);
}
TEST(stable_step_reversed, t1)
{
    EXPECT_FALSE(false);
}

#endif // STABLE