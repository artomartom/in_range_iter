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

TEST(basic, t1){
    // basic_assert<char>(0, 10, 1);
    // basic_assert<short>(0, 10, 1);
    // basic_assert<int>(0, 10, 1);
    // basic_assert<int8_t>(0, 10, 1);
    // basic_assert<int16_t>(0, 10, 1);
    // basic_assert<int32_t>(0, 10, 1);
    // basic_assert<int64_t>(0, 10, 1);
    // basic_assert<long>(0, 10, 1);
    // basic_assert<long long>(0, 10, 1);
    // basic_assert<unsigned char>(0, 10, 1);
    // basic_assert<unsigned short>(0, 10, 1);
    // basic_assert<unsigned int>(0, 10, 1);
    // basic_assert<unsigned int8_t>(0, 10, 1);
    // basic_assert<unsigned int16_t>(0, 10, 1);
    // basic_assert<unsigned int32_t>(0, 10, 1);
    // basic_assert<unsigned int64_t>(0, 10, 1);
    // basic_assert<unsigned long>(0, 10, 1);
    // basic_assert<unsigned long long>(0, 10, 1);

};

template <typename T>
void test_all(){
    // auto a_us{()[]{return std::rand() - std::rand()}}; // accidentally_unsigned
    // for (int i{}; i != 10'000; ++i)
    // {
    //     basic_assert<T>(std::rand(), std::rand(), std::rand());
    //     assert_with_jumps<T>(std::rand(), std::rand(), std::rand(), std::rand(), std::rand());
    //     basic_assert<T>(a_us(), a_us(), a_us());
    //     assert_with_jumps<T>(a_us(), a_us(), a_us(), a_us());
    // }
};

TEST(unstable, t1)
{
    auto ran = in_range<int>(0, 10);
    auto begin = ran.begin();
    auto end = ran.end();
    std::cout << sizeof(begin) << '\n';
    std::cout << sizeof(end) << '\n';
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