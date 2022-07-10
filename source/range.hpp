#ifndef RANGE_HPP
#define RANGE_HPP

namespace ranges
{

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
    struct step
    {
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

    template <typename T>
    class range //  range object
    {

    public:
        struct iterator
        {
        public:
            explicit iterator(T index)
                : m_index(index){};
            iterator() = delete;
            virtual ~iterator() = default;

            bool operator!=(const iterator &other) const noexcept { return m_index > other.m_index; };
            T &operator++() noexcept { return ++m_index; };
            T operator*() noexcept { return m_index; };

        protected:
            T m_index{};
        };

        template <typename U, typename... Args> // factory
        friend auto in_range(U begin, U end, Args... args) noexcept;

        range::iterator begin() const noexcept { return range::iterator{this->m_begin}; };
        range::iterator end() const noexcept { return range::iterator{this->m_end}; };

    protected:
        template <typename... Args>
        explicit range(T begin, T end, Args...) noexcept
            : m_begin(begin), m_end(end){};
        T m_begin;
        T m_end;
    };
    template <typename T>
    class reversed_range : public range<T> //  range object
    {

    public:
        struct iterator : public range<T>::iterator
        {
        public:
            explicit iterator(T index) noexcept
                : range<T>::iterator{index} {};
            bool operator!=(const iterator &other) const noexcept { return this->m_index != other.m_index; };
            T &operator++() noexcept { return --iterator::m_index; };
        };
        template <typename U, typename... Args> // factory
        friend auto in_range(U begin, U end, Args... args) noexcept;

        reversed_range::iterator begin() const noexcept { return reversed_range::iterator{this->m_begin}; };
        reversed_range::iterator end() const noexcept { return reversed_range::iterator{this->m_end}; };

    protected:
        template <typename... Args>
        explicit reversed_range(T begin, T end, Args...) noexcept
            : range<T>{begin - 1, end} {};
    };
    template <typename T>
    class step_range : protected range<T> //  range object
    {

    public:
        struct iterator : public range<T>::iterator
        {
        public:
            explicit iterator(T index, T step) noexcept
                : range<T>::iterator{index},
                  m_step{step} {};
            T &operator++() noexcept { return this->m_index += m_step; };

        protected:
            T m_step;
        };

        template <typename U, typename... Args> // factory
        friend auto in_range(U begin, U end, Args... args) noexcept;

        step_range::iterator begin() const noexcept { return step_range::iterator{this->m_begin, this->m_step}; };
        step_range::iterator end() const noexcept { return step_range::iterator{this->m_end, this->m_step}; };

    protected:
        template <typename... Args>
        explicit step_range(T begin, T end, T step, Args...) noexcept
            : range<T>{begin, end},
              m_step{step} {};
        T m_step;
    };
    template <typename T>
    class reversed_step_range : protected range<T> //  range object
    {

    public:
        struct iterator : public step_range<T>::iterator
        {
        public:
            explicit iterator(T index, T step) noexcept
                : step_range<T>::iterator{index, step} {};
            bool operator!=(const iterator &other) const noexcept { return this->m_index >= other.m_index; };
            T &operator++() noexcept { return iterator::m_index += this->m_step; };
        };

        template <typename U, typename... Args> // factory
        friend auto in_range(U begin, U end, Args... args) noexcept;

        reversed_step_range::iterator begin() const noexcept { return reversed_step_range::iterator{this->m_begin, this->m_step}; };
        reversed_step_range::iterator end() const noexcept { return reversed_step_range::iterator{this->m_end, this->m_step}; };

    protected:
        template <typename... Args>
        explicit reversed_step_range(T begin, T end, T step, Args...) noexcept
            : step_range<T>{begin - 1, end, step} {};
    };

    //  outside  decls for friend function (cause of wierd c++ friend func visibility)
    // factories

    template <typename U, typename... Args>
    auto in_range(U begin, U end, Args... args) noexcept
    {
        constexpr bool use_stable{util::is_present<stable, Args...>::value};
        constexpr bool use_step{util::is_present<step, Args...>::value};
        constexpr bool use_reversed{util::is_present<reversed, Args...>::value};
        if constexpr (use_stable)
        {
            return range{begin, end};
        }
        else
        {

            if constexpr (use_step && use_reversed)
                return reversed_step_range{begin, end, args...};
            if constexpr (use_step)
                return step_range{begin, end, args...};
            if constexpr (use_reversed)
                return reversed_range{begin, end, args...};
            else
                return range{begin, end, args...};
        }
    };
        // stable factory
#undef STABLE
#ifdef STABLE
    inline range in_range(range::T begin, range::T end, stable) noexcept
    {
        if (begin > end)
            return range{end, begin};
        else
            return range{begin, end};
    };
    inline reversed_range reversed_in_range(reversed_range::T begin, reversed_range::T end, stable) noexcept
    {
        //     if (begin > end)else
        return reversed_range{begin, end};
    };
    inline step_range in_range(step_range::T begin, step_range::T end, step_range::T step, stable) noexcept
    {
        // if(step<0 )       step=-step;

        //     if (begin > end)else
        return step_range{begin, end, step};
    };
    inline reversed_step_range reversed_in_range(reversed_step_range::T begin, reversed_step_range::T end, reversed_step_range::T step, stable) noexcept
    {
        // if(step<0 )       step=-step;
        //      if (begin > end)else
        return reversed_step_range{begin, end, step};
    };
#endif // STABLE

};

#endif // RANGE_HPP
