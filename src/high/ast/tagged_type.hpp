#pragma once

#include <string>
#include <vector>
// Define primitive types
enum class PrimitiveType { Unit, I8, I16, I32, I64, ISIZE, U8, U16, U32, U64, USIZE, Char, Bool };

// Convert PrimitiveType to string for representation
std::string primitive_type_to_string(PrimitiveType pt) {
    switch (pt) {
    case PrimitiveType::Unit:
        return "Unit";
    case PrimitiveType::I8:
        return "I8";
    case PrimitiveType::I16:
        return "I16";
    case PrimitiveType::I32:
        return "I32";
    case PrimitiveType::I64:
        return "I64";
    case PrimitiveType::ISIZE:
        return "ISIZE";
    case PrimitiveType::U8:
        return "U8";
    case PrimitiveType::U16:
        return "U16";
    case PrimitiveType::U32:
        return "U32";
    case PrimitiveType::U64:
        return "U64";
    case PrimitiveType::USIZE:
        return "USIZE";
    case PrimitiveType::Char:
        return "Char";
    case PrimitiveType::Bool:
        return "Bool";
    default:
        return "Unknown";
    }
}

// Tagged union for Type
struct Type {
    // Enum for active type
    enum class Tag {
        Primitive,
        Tuple,
        Array,
        UserDefined,
    };

    static const unsigned char ref_flag = 0b01;
    static const unsigned char ref_mut_flag = 0b10;

    // Members
    Tag tag;
    unsigned char _reference_flags = 0;
    union {
        PrimitiveType primitive;
        std::vector<Type> tuple;
        struct {
            Type *t;
            size_t len;
        } array;
        std::string user_defined;
    };

    // Constructors
    Type()
        : tag(Tag::Primitive)
        , _reference_flags(0)
        , primitive(PrimitiveType::Unit) {}

    Type(PrimitiveType t, unsigned char flags)
        : tag(Tag::Primitive)
        , _reference_flags(flags)
        , primitive(t) {}

    Type(const std::string &s, unsigned char flags)
        : tag(Tag::UserDefined)
        , _reference_flags(flags)
        , user_defined(s) {}

    Type(const std::vector<Type> &ts, unsigned char flags)
        : tag(Tag::Tuple)
        , _reference_flags(flags)
        , tuple(ts) {}

    Type(const Type &t, size_t len, unsigned char flags)
        : tag(Tag::Array)
        , array{new Type(t), len}
        , _reference_flags(flags) {}

    // Destructor
    ~Type() {
        switch (tag) {
        case Tag::UserDefined:
            user_defined.~basic_string();
            break;
        case Tag::Tuple:
            tuple.~vector();
            break;
        default: {
        }
        }
    }

    // Copy constructor
    Type(const Type &other)
        : tag(other.tag)
        , _reference_flags(other._reference_flags) {
        switch (tag) {
        case Tag::Primitive:
            primitive = other.primitive;
            break;
        case Tag::UserDefined:
            new (&user_defined) std::string(other.user_defined);
            break;
        case Tag::Tuple:
            new (&tuple) std::vector(other.tuple);
            break;
        case Tag::Array:
            array.t = other.array.t;
            array.len = other.array.len;
            break;
        }
    }

    // Move constructor
    Type(Type &&other) noexcept
        : tag(other.tag)
        , _reference_flags(other._reference_flags) {
        switch (tag) {
        case Tag::Primitive:
            primitive = other.primitive;
            break;
        case Tag::UserDefined:
            new (&user_defined) std::string(std::move(other.user_defined));
            break;
        case Tag::Array:
            array.t = other.array.t;
            array.len = other.array.len;
            break;
        case Tag::Tuple:
            new (&tuple) std::vector(std::move(other.tuple));
            break;
        }
    }

    // Assignment operators
    Type &operator=(const Type &other) {
        if (this != &other) {
            this->~Type();
            new (this) Type(other);
        }
        return *this;
    }

    Type &operator=(Type &&other) noexcept {
        if (this != &other) {
            this->~Type();
            new (this) Type(std::move(other));
        }
        return *this;
    }

    // Utility functions
    bool is_primitive() const { return tag == Tag::Primitive; }

    bool is_ref() const { return _reference_flags == ref_flag; }

    bool is_mut_ref() const { return _reference_flags == ref_mut_flag; }

    std::string to_string() const {
        if (tag == Tag::Primitive) {
            return primitive_type_to_string(primitive);
        } else if (tag == Tag::UserDefined) {
            return user_defined;
        } else if (tag == Tag::Tuple) {
            std::string result = "(";
            for (const auto &t : tuple) {
                result += t.to_string() += ", ";
            }
            result += ")";
            return result;
        } else if (tag == Tag::Array) {
            std::string result = "[";
            result += array.t->to_string() + ';' + std::to_string(array.len);
            result += "]";
            return result;
        }
        return "Invalid Type";
    }
};