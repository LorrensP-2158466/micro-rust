#pragma once

#include <memory>
#include <variant>
#include <optional>

namespace mr
{
    // i hate typing "std::unique_ptr" constantly
    template<typename T>
    using Unique = std::unique_ptr<T>;

    template<typename T>
    using OptUnique = std::optional<Unique<T>>;

    inline const char* const bool_to_str(const bool b){
        return b ? "true" : "false";
    }

     // helper type for the visitor #4
    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };

    // explicit deduction guide (not needed as of C++20)
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

    template <typename To, typename From, typename Deleter> 
    std::unique_ptr<To, Deleter> dynamic_unique_cast(std::unique_ptr<From, Deleter>&& p) {
        if (To* cast = dynamic_cast<To*>(p.get()))
        {
            std::unique_ptr<To, Deleter> result(cast, std::move(p.get_deleter()));
            p.release();
            return result;
        }
        return std::unique_ptr<To, Deleter>(nullptr); // or throw std::bad_cast() if you prefer
    }

    template<typename T>
    class slice{
        const T* _p;
        size_t _len;
        public:
            slice(const T* p, size_t len)
                : _p(p)
                , _len(len)
                {}
        
        struct Iterator {
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = const value_type*;  
            using reference         = const value_type&;  

            // Iterator constructors here...
            Iterator(const pointer p)
                : _ptr(p) 
                {}
            reference operator*() const { return *_ptr; }
            pointer operator->() { return _ptr; }

            // Prefix increment
            Iterator& operator++() { _ptr++; return *this; }  

            // Postfix increment
            Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

            friend bool operator== (const Iterator& a, const Iterator& b) { return a._ptr == b._ptr; };
            friend bool operator!= (const Iterator& a, const Iterator& b) { return a._ptr != b._ptr; };     

        private:

            pointer _ptr;
        };  
        Iterator begin() { return Iterator(_p); };
        Iterator end()   { return Iterator(_p + _len); }; // 200 is out of bounds
    };
} // namespace mr


