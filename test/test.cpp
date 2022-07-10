#include <gtest/gtest.h>
#define STABLE
#include <chrono>
#include <type_traits>
#include <boost/type_index.hpp>
#include <tuple>
#include <range.hpp>

template <class T>
const char *getType(T)
{
    return boost::typeindex::type_id<T>().pretty_name().c_str();
}

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
void basic_assert(T from, T to, T step = 1, T jump_rate = 1)
{

    for (T i{}; auto e : in_range<T>(from, to))
    {
        ASSERT_TRUE(i >= from) << i << ' ' << e << ' ' << from << ' ' << to << ' ' << " with T == " << getType(to);
        ASSERT_TRUE(i < to) << i << ' ' << e << ' ' << from << ' ' << to << ' ' << " with T == " << getType(to);
        ASSERT_TRUE(e == i) << i << ' ' << e << ' ' << from << ' ' << to << ' ' << " with T == " << getType(to);

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
    auto a_us{[]()
              { return std::rand() - std::rand(); }}; // accidentally_unsigned
    for (int i{}; i != 1'000; ++i)
    {
        basic_assert<T>(std::rand(), std::rand(), std::rand(), std::rand());
        basic_assert<T>(a_us(), a_us(), a_us(), a_us());
    }
};

TEST(basic, t1)
{
    // test_all<char>();
    // test_all<short>();
    // test_all<int>();
    test_all<long>();
    // test_all<long long>();
    // test_all<unsigned char>();
    // test_all<unsigned short>();
    // test_all<unsigned int>();
    // test_all<unsigned long>();
    // test_all<unsigned long long>();
};
