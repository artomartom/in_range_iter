//#ifndef RANGE_HPP
//#define RANGE_HPP
#include <iostream>
#include <type_traits>
#include <assert.h>

namespace util
{

    template <typename What, typename... Args>
    struct is_present
    {
        static constexpr bool value{(std::is_same_v<What, Args> || ...)};
    };
};

struct stable
{
};

template <typename U>
struct step
{
    template <typename T, bool>
    struct range;

    template <typename T, bool>
    struct iterator;

    template <typename T>
    struct range<T, true>
    {
        T m_step;
    };
    template <typename T>
    struct iterator<T, true>
    {
        T m_step;
    };
    template <typename T>
    struct range<T, false>
    {
    };
    template <typename T>
    struct iterator<T, false>
    {
    };
};

struct reversed
{
};

template <typename T>
struct range_iterator_trait
{
    using value_type = T;
    using difference_type = decltype(value_type{} - value_type{});
    using iterator_category = std::input_iterator_tag;
    using pointer = value_type *;
    using reference = value_type &;
};

template <typename T, typename... Flags>
class range : public step<T>::range<T, util::is_present<step<T>, Flags...>::value> //  range object
{
    static constexpr bool use_step{util::is_present<step<T>, Flags...>::value};
    static constexpr bool use_reversed{util::is_present<reversed, Flags...>::value};
    static constexpr bool use_stable{util::is_present<stable, Flags...>::value};

public:
    struct iterator : public step<T>::iterator<T, use_step>
    {
    public:
        explicit iterator(T index)
            : m_index(index){};
        iterator() = delete;
        iterator(iterator &&) = delete;
        iterator(const iterator &) = delete;
        ~iterator() = default;
        T operator*() noexcept { return m_index; };
        bool operator!=(const iterator &other) const noexcept
        {
            // if constexpr (util::is_present<step<T>, Flags...>::value || sizeof...(Flags) == 0)
            // return m_index > other.m_index;
            return m_index > other.m_index;
        };
        T &operator++() noexcept
        {

            // if constexpr (util::is_present<step<T>, Flags...>::value)
            //     return this->m_index += this->m_step;
            return ++m_index;
        };

    protected:
        T m_index;
    };

    template <typename U, typename... Args> // factory
    friend range<U> in_range(U begin, U end, Args... args) noexcept;

    iterator begin() const noexcept { return iterator{this->m_begin}; };
    iterator end() const noexcept { return iterator{this->m_end}; };

    range(T begin, T end, Flags... flags) noexcept
    {
        if constexpr (use_step &&)

            m_begin = begin;
        m_end = end;
    };

protected:
    T m_begin;
    T m_end;
};

template <typename U, typename... Args>
range<U, Args...> in_range(U begin, U end, Args... args) noexcept
{
    return range{begin, end, args...};
};

int main()
{
    auto ran{in_range(0, 10)};

    // for (auto i : ran)
    //     std::cout << i << "\n";

    auto begin{ran.begin()};
    auto end{ran.end()};
    std::cout << *begin;
    std::cout << *end;

    for (; begin != end; ++begin)
        std::cout << *begin << "\n";

    // static_assert(sizeof(begin)==sizeof(int));
    // static_assert(sizeof(end)==sizeof(int));

    return 0;
}

//#endif // RANGE_HPP