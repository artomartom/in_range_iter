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

    struct range
    {

        using index_t = range_iterator_trait<int>::value_type;

    public:
        struct iterator
        {
        public:
            explicit iterator(index_t index)
                : m_index(index){};
            iterator() = delete;
            virtual ~iterator() = default;

            bool operator!=(const iterator &other) const noexcept { return m_index != other.m_index; };
            index_t &operator++() noexcept { return ++m_index; };
            index_t operator*() noexcept { return m_index; };

        protected:
            index_t m_index{};
        };

        // factory
        friend inline range in_range(index_t begin, index_t end);
        friend inline range in_range(index_t begin, index_t end, stable);

        iterator begin() const noexcept { return iterator{m_begin}; };
        iterator end() const noexcept { return iterator{m_end}; };

    protected:
        explicit range(index_t begin, index_t end)
            : m_begin(begin), m_end(end){};
        index_t m_begin;
        index_t m_end;
    };

    struct reversed_range : public range
    {

        using index_t = range_iterator_trait<int>::value_type;

    public:
        struct iterator : public range::iterator
        {
        public:
            explicit iterator(index_t index)
                : range::iterator{index} {};
            bool operator!=(const iterator &other) const noexcept { return m_index != other.m_index; };
            index_t &operator++() noexcept { return --iterator::m_index; };
        };
        // factory
        friend inline reversed_range reversed_in_range(index_t begin, index_t end);
        friend inline reversed_range reversed_in_range(index_t begin, index_t end, stable);

        iterator begin() const noexcept { return iterator{range::m_begin}; };
        iterator end() const noexcept { return iterator{range::m_end}; };

    protected:
        explicit reversed_range(index_t begin, index_t end)
            : range{begin - 1, end} {};
    };
    struct step_range : protected range
    {

        using index_t = range_iterator_trait<int>::value_type;

    public:
        struct iterator : public range::iterator
        {
        public:
            explicit iterator(index_t index, index_t step)
                : range::iterator{index},
                  m_step{step} {};
            index_t &operator++() noexcept { return iterator::m_index += m_step; };

        protected:
            index_t m_step{};
        };
        // factory
        friend inline step_range in_range(index_t begin, index_t end, index_t step);
        friend inline step_range in_range(index_t begin, index_t end, index_t step, stable);

        iterator begin() const noexcept { return iterator{range::m_begin, m_step}; };
        iterator end() const noexcept { return iterator{range::m_end, m_step}; };

    protected:
        explicit step_range(index_t begin, index_t end, index_t step)
            : range{begin, end},
              m_step{step} {};
        index_t m_step{};
    };

    struct reversed_step_range : protected step_range
    {

        using index_t = range_iterator_trait<int>::value_type;

    public:
        struct iterator : public step_range::iterator
        {
        public:
            explicit iterator(index_t index, index_t step)
                : step_range::iterator{index, step} {};
            bool operator!=(const iterator &other) const noexcept { return m_index >= other.m_index; };
            index_t &operator++() noexcept { return iterator::m_index += m_step; };
        };
        // factory
        friend inline reversed_step_range reversed_in_range(index_t begin, index_t end, index_t step);
        friend inline reversed_step_range reversed_in_range(index_t begin, index_t end, index_t step, stable);

        iterator begin() const noexcept { return iterator{range::m_begin, m_step}; };
        iterator end() const noexcept { return iterator{range::m_end, m_step}; };

    protected:
        explicit reversed_step_range(index_t begin, index_t end, index_t step)
            : step_range{begin - 1, end, step} {};
    };

    // factory
    inline range in_range(range::index_t begin, range::index_t end)
    {
        return range{begin, end};
    };
    inline reversed_range reversed_in_range(reversed_range::index_t begin, reversed_range::index_t end)
    {
        return reversed_range{begin, end};
    };
    inline step_range in_range(step_range::index_t begin, step_range::index_t end, step_range::index_t step)
    {
        return step_range{begin, end, step};
    };
    inline reversed_step_range reversed_in_range(reversed_step_range::index_t begin, reversed_step_range::index_t end, reversed_step_range::index_t step)
    {
        return reversed_step_range{begin, end, step};
    };

// stable factory

#ifdef STABLE
    inline range in_range(range::index_t begin, range::index_t end, stable)
    {
        if (begin > end)
            return range{end, begin};
        else
            return range{begin, end};
    };
    inline reversed_range reversed_in_range(reversed_range::index_t begin, reversed_range::index_t end, stable)
    {
        //     if (begin > end)else
        return reversed_range{begin, end};
    };
    inline step_range in_range(step_range::index_t begin, step_range::index_t end, step_range::index_t step, stable)
    {
        // if(step<0 )       step=-step;

        //     if (begin > end)else
        return step_range{begin, end, step};
    };
    inline reversed_step_range reversed_in_range(reversed_step_range::index_t begin, reversed_step_range::index_t end, reversed_step_range::index_t step, stable)
    {
        // if(step<0 )       step=-step;
        //      if (begin > end)else
        return reversed_step_range{begin, end, step};
    };
#endif // STABLE

};

#endif // RANGE_HPP
