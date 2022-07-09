#ifndef RANGE_HPP
#define RANGE_HPP

namespace ranges
{
    struct stable
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

        using index_t = range_iterator_trait<T>::value_type;

    public:
        struct iterator
        {
        public:
            explicit iterator(index_t index)
                : m_index(index){};
            iterator() = delete;
            virtual ~iterator() = default;

            bool operator!=(const iterator &other) const noexcept { return m_index > other.m_index; };
            index_t &operator++() noexcept { return ++m_index; };
            index_t operator*() noexcept { return m_index; };

        protected:
            index_t m_index{};
        };

        template <typename U> // factory
        friend range<U> in_range(U begin, U end) noexcept;
        template <typename U> // factory
        friend range<U> in_range(U begin, U end, stable) noexcept;

        range::iterator begin() const noexcept { return range::iterator{this->m_begin}; };
        range::iterator end() const noexcept { return range::iterator{this->m_end}; };

    protected:
        explicit range(index_t begin, index_t end) noexcept
            : m_begin(begin), m_end(end){};
        index_t m_begin;
        index_t m_end;
    };
    template <typename T>
    class reversed_range : public range<T> //  range object
    {

        using index_t = range_iterator_trait<T>::value_type;

    public:
        struct iterator : public range<T>::iterator
        {
        public:
            explicit iterator(index_t index) noexcept
                : range<T>::iterator{index} {};
            bool operator!=(const iterator &other) const noexcept { return this->m_index != other.m_index; };
            index_t &operator++() noexcept { return --iterator::m_index; };
        };

        template <typename U> // factory
        friend reversed_range<U> reversed_in_range(U begin, U end) noexcept;
        template <typename U> // factory
        friend reversed_range<U> reversed_in_range(U begin, U end, stable) noexcept;

        reversed_range::iterator begin() const noexcept { return reversed_range::iterator{this->m_begin}; };
        reversed_range::iterator end() const noexcept { return reversed_range::iterator{this->m_end}; };

    protected:
        explicit reversed_range(index_t begin, index_t end) noexcept
            : range<T>{begin - 1, end} {};
    };
    template <typename T>
    class step_range : protected range<T> //  range object
    {

        using index_t = range_iterator_trait<T>::value_type;

    public:
        struct iterator : public range<T>::iterator
        {
        public:
            explicit iterator(index_t index, index_t step) noexcept
                : range<T>::iterator{index},
                  m_step{step} {};
            index_t &operator++() noexcept { return this->m_index += m_step; };

        protected:
            index_t m_step{};
        };

        template <typename U> // factory
        friend step_range<U> in_range(U begin, U end, U step) noexcept;
        template <typename U> // factory
        friend step_range<U> in_range(U begin, U end, U step, stable) noexcept;

        step_range::iterator begin() const noexcept { return step_range::iterator{this->m_begin, this->m_step}; };
        step_range::iterator end() const noexcept { return step_range::iterator{this->m_end, this->m_step}; };

    protected:
        explicit step_range(index_t begin, index_t end, index_t step) noexcept
            : range<T>{begin, end},
              m_step{step} {};
        index_t m_step{};
    };
    template <typename T>
    class reversed_step_range : protected range<T> //  range object
    {

        using index_t = range_iterator_trait<T>::value_type;

    public:
        struct iterator : public step_range<T>::iterator
        {
        public:
            explicit iterator(index_t index, index_t step) noexcept
                : step_range<T>::iterator{index, step} {};
            bool operator!=(const iterator &other) const noexcept { return this->m_index >= other.m_index; };
            index_t &operator++() noexcept { return iterator::m_index += this->m_step; };
        };

        template <typename U> // factory
        friend reversed_step_range<U> reversed_in_range(U begin, U end, U step) noexcept;
        template <typename U> // factory
        friend reversed_step_range<U> reversed_in_range(U begin, U end, U step, stable) noexcept;

        reversed_step_range::iterator begin() const noexcept { return reversed_step_range::iterator{this->m_begin, this->m_step}; };
        reversed_step_range::iterator end() const noexcept { return reversed_step_range::iterator{this->m_end, this->m_step}; };

    protected:
        explicit reversed_step_range(index_t begin, index_t end, index_t step) noexcept
            : step_range<T>{begin - 1, end, step} {};
    };

    //  outside  decls for friend function (cause of wierd c++ friend func visibility)
    // factories

    template <typename U>
    range<U> in_range(U begin, U end) noexcept
    {
        return range<U>{begin, end};
    };
    template <typename U>
    range<U> in_range(U begin, U end, stable) noexcept
    {
        return range<U>{};
    };
    template <typename U>
    reversed_range<U> reversed_in_range(U begin, U end) noexcept
    {
        return reversed_range<U>{begin, end};
    };
    template <typename U>
    reversed_range<U> reversed_in_range(U begin, U end, stable) noexcept
    {
        return reversed_range<U>{};
    };
    template <typename U>
    step_range<U> in_range(U begin, U end, U step) noexcept
    {
        return step_range<U>{begin, end, step};
    };
    template <typename U>
    step_range<U> in_range(U begin, U end, U step, stable) noexcept
    {
        return step_range<U>{};
    };
    template <typename U>
    reversed_step_range<U> reversed_in_range(U begin, U end, U step) noexcept
    {
        return reversed_step_range<U>{begin, end, step};
    };
    template <typename U>
    reversed_step_range<U> reversed_in_range(U begin, U end, U step, stable) noexcept
    {
        return reversed_step_range<U>{};
    };

        // stable factory
#undef STABLE
#ifdef STABLE
    inline range in_range(range::index_t begin, range::index_t end, stable) noexcept
    {
        if (begin > end)
            return range{end, begin};
        else
            return range{begin, end};
    };
    inline reversed_range reversed_in_range(reversed_range::index_t begin, reversed_range::index_t end, stable) noexcept
    {
        //     if (begin > end)else
        return reversed_range{begin, end};
    };
    inline step_range in_range(step_range::index_t begin, step_range::index_t end, step_range::index_t step, stable) noexcept
    {
        // if(step<0 )       step=-step;

        //     if (begin > end)else
        return step_range{begin, end, step};
    };
    inline reversed_step_range reversed_in_range(reversed_step_range::index_t begin, reversed_step_range::index_t end, reversed_step_range::index_t step, stable) noexcept
    {
        // if(step<0 )       step=-step;
        //      if (begin > end)else
        return reversed_step_range{begin, end, step};
    };
#endif // STABLE

};

#endif // RANGE_HPP
