#pragma once

#include "iterators.hpp"
#include <concepts>
#include <cstddef>
#include <deque>
#include <functional>
#include <span>
#include <type_traits>
#include <vector>

namespace mr {
template <typename K>
concept Key = requires(K k) {
    { k.id() } -> std::same_as<size_t>;
} && std::is_constructible_v<K, size_t>;

// port of rust workqueue

// Concept to ensure the template parameter meets our index.id requirements

// BitSet implementation for tracking presence of elements
template <Key T> struct BitSet {
    std::vector<bool> bits;

    explicit BitSet(size_t size)
        : bits(size, false) {}
    static BitSet all_set(size_t size) {
        BitSet result(size);
        result.bits.flip();
        return result;
    }

    inline bool insert(T index) {
        if (index.id() >= bits.size() || bits[index.id()]) {
            return false;
        }
        bits[index.id()] = true;
        return true;
    }

    void remove(T index) {
        if (index.id() < bits.size()) {
            bits[index.id()] = false;
        }
    }

    static bool bit_wise(BitSet &out, const BitSet &in, std::function<bool(bool, bool)> &&op) {
        if (out.bits.size() != in.bits.size()) {
            throw std::invalid_argument("Sets must be of equal size");
        }
        bool changed = false;
        for (size_t i = 0; i < out.bits.size(); ++i) {
            bool old_elem = out.bits[i];
            bool in_elem = in.bits[i];
            bool new_elem = op(old_elem, in_elem);
            out.bits[i] = new_elem;
            changed |= old_elem != new_elem;
        }
        return changed;
    }

    bool union_changed(const BitSet &other) {
        return bit_wise(*this, other, [](bool a, bool b) { return a || b; });
    }

    bool intersection_changed(const BitSet &other) {
        return bit_wise(*this, other, [](bool a, bool b) { return a && b; });
    }

    // Set union (|)
    BitSet operator|(const BitSet &other) const {
        if (bits.size() != other.bits.size()) {
            throw std::invalid_argument("Sets must be of equal size");
        }
        BitSet result(bits.size());
        for (size_t i = 0; i < bits.size(); ++i) {
            result.bits[i] = bits[i] || other.bits[i];
        }
        return result;
    }

    // Set intersection (&)
    BitSet operator&(const BitSet &other) const {
        if (bits.size() != other.bits.size()) {
            throw std::invalid_argument("Sets must be of equal size");
        }
        BitSet result(bits.size());
        for (size_t i = 0; i < bits.size(); ++i) {
            result.bits[i] = bits[i] && other.bits[i];
        }
        return result;
    }

    // Set difference (-)
    BitSet operator-(const BitSet &other) const {
        if (bits.size() != other.bits.size()) {
            throw std::invalid_argument("Sets must be of equal size");
        }
        BitSet result(bits.size());
        for (size_t i = 0; i < bits.size(); ++i) {
            result.bits[i] = bits[i] && !other.bits[i];
        }
        return result;
    }

    BitSet &complement() {
        for (size_t i = 0; i < bits.size(); ++i) {
            bits[i] = !bits[i];
        }
        return *this;
    }

    // Equality operator (==)
    bool operator==(const BitSet &other) const { return bits == other.bits; }

    // Inequality operator (!=)
    bool operator!=(const BitSet &other) const { return !(*this == other); }

    // Subset operator (<=)
    bool operator<=(const BitSet &other) const {
        if (bits.size() != other.bits.size()) {
            throw std::invalid_argument("Sets must be of equal size");
        }
        for (size_t i = 0; i < bits.size(); ++i) {
            if (bits[i] && !other.bits[i])
                return false;
        }
        return true;
    }

    // Proper subset operator (<)
    bool operator<(const BitSet &other) const { return *this <= other && *this != other; }

    // Superset operator (>=)
    bool operator>=(const BitSet &other) const { return other <= *this; }

    // Proper superset operator (>)
    bool operator>(const BitSet &other) const { return other < *this; }

    // Compound assignment operators
    BitSet &operator|=(const BitSet &other) {
        if (bits.size() != other.bits.size()) {
            throw std::invalid_argument("Sets must be of equal size");
        }
        for (size_t i = 0; i < bits.size(); ++i) {
            bits[i] = bits[i] || other.bits[i];
        }
        return *this;
    }

    BitSet &operator&=(const BitSet &other) {
        if (bits.size() != other.bits.size()) {
            throw std::invalid_argument("Sets must be of equal size");
        }
        for (size_t i = 0; i < bits.size(); ++i) {
            bits[i] = bits[i] && other.bits[i];
        }
        return *this;
    }

    BitSet &operator-=(const BitSet &other) {
        if (bits.size() != other.bits.size()) {
            throw std::invalid_argument("Sets must be of equal size");
        }
        for (size_t i = 0; i < bits.size(); ++i) {
            bits[i] = bits[i] && !other.bits[i];
        }
        return *this;
    }

    // Utility methods
    bool empty() const {
        return std::none_of(bits.begin(), bits.end(), [](bool b) { return b; });
    }

    size_t size() const { return bits.size(); }

    size_t count() const { return std::count(bits.begin(), bits.end(), true); }

    bool contains(T index) const { return index.id() < bits.size() && bits[index.id()]; }
};

template <typename T> class WorkQueue {
  private:
    std::deque<T> deque;
    BitSet<T> set;

  public:
    // Creates a new work queue that starts empty, where elements range from [0, len)
    explicit WorkQueue(size_t len)
        : deque()
        , set(len) {}

    // Attempt to enqueue element in the work queue. Returns false if it was already
    // present
    bool insert(T element) {
        if (set.insert(element)) {
            deque.push_back(element);
            return true;
        }
        return false;
    }

    // Attempt to pop an element from the work queue
    std::optional<T> pop() {
        if (deque.empty()) {
            return std::nullopt;
        }
        T element = deque.front();
        deque.pop_front();
        set.remove(element);
        return element;
    }
};
} // namespace mr