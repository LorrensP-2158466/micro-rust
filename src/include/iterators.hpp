#pragma once

#include <iterator>
#include <tuple>

namespace mr { namespace iterators {

    template <typename... Iters> class zip_iterator {
        std::tuple<Iters...> iterators;

      public:
        using iterator_category = std::input_iterator_tag;
        using value_type = std::tuple<typename std::iterator_traits<Iters>::value_type...>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type;

        zip_iterator(Iters... its)
            : iterators(its...) {}

        zip_iterator &operator++() {
            std::apply([](auto &...its) { ((++its), ...); }, iterators);
            return *this;
        }

        zip_iterator operator++(int) {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        value_type operator*() {
            return std::apply([](auto &...its) { return std::make_tuple((*its)...); }, iterators);
        }

        value_type operator*() const {
            return std::apply([](const auto &...its) { return std::make_tuple((*its)...); }, iterators);
        }

        bool operator==(const zip_iterator &other) const { return iterators == other.iterators; }

        bool operator!=(const zip_iterator &other) const { return !(*this == other); }
    };

    // Helper function to create zip iterators
    template <typename... Iters> zip_iterator<Iters...> make_zip_iterator(Iters... its) {
        return zip_iterator<Iters...>(its...);
    }

    // Helper class to create begin and end iterators
    template <typename... Containers> class zip_view {
        std::tuple<Containers &...> containers;

      public:
        zip_view(Containers &...conts)
            : containers(conts...) {}

        auto begin() {
            return std::apply([](auto &...conts) { return make_zip_iterator(conts.begin()...); }, containers);
        }

        auto end() {
            return std::apply([](auto &...conts) { return make_zip_iterator(conts.end()...); }, containers);
        }

        auto begin() const {
            return std::apply([](const auto &...conts) { return make_zip_iterator(conts.begin()...); }, containers);
        }

        auto end() const {
            return std::apply([](const auto &...conts) { return make_zip_iterator(conts.end()...); }, containers);
        }
    };

    template <typename... Containers> auto zip(Containers &...conts) { return zip_view<Containers...>(conts...); }

    template <typename... Containers> auto zip(const Containers &...conts) {
        return zip_view<const Containers...>(conts...);
    }
}} // namespace mr::iterators
