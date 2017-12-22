#pragma once
#include <iosfwd>
#include <limits>
#include <type_traits>

namespace olymp {
namespace modulo {

template<class T>
constexpr bool is_unsigned = std::is_unsigned<T>::value;

template<class T>
constexpr bool is_signed = std::is_signed<T>::value;

template <unsigned long long Modulo, class T = unsigned long long, class = void>
class Int;

template <unsigned long long Modulo, class T>
class Int<Modulo, T, std::enable_if_t<is_unsigned<T>>> {
    using Self = Int<Modulo, T>;

public:
    explicit Int(T init) : value(init % Modulo) {}

    template <class U, std::enable_if_t<is_unsigned<U>> * = nullptr>
    Self &operator+=(const U u) {
        static_assert(std::numeric_limits<T>::max() / 2 >= Modulo,
                      "Modulo is too large to work with this type of integer");
        value += (u % Modulo);
        value %= Modulo;
        return *this;
    }

    template <class U, std::enable_if_t<is_signed<U>> * = nullptr>
    Self &operator+=(U u) {
        return this->operator+=(invert_negative(u));
    }

    template <class U, std::enable_if_t<is_signed<U>> * = nullptr>
    Self &operator-=(const U u) {
        return this->operator+=(U(-u));
    }

    template <class U, std::enable_if_t<is_unsigned<U>> * = nullptr>
    Self &operator*=(const U u) {
        static_assert(std::numeric_limits<T>::max() / Modulo >= Modulo,
                      "Modulo is too large to work with this type of integer");
        value *= (u % Modulo);
        value %= Modulo;
        return *this;
    }

    template <class U, std::enable_if_t<is_signed<U>> * = nullptr>
    Self &operator*=(U u) {
        return this->operator*=(invert_negative(u));
    }

    Self operator++() {
        return (*this) += 1;
    }

    Self operator--() {
        return (*this) -= 1;
    }

    bool operator<(Self other) const { return value < other.value; }
    bool operator==(Self other) const { return value == other.value; }
    bool operator<=(Self other) const { return *this < other || *this == other; }
    bool operator>(Self other) const { return other < *this; }
    bool operator!=(Self other) const { return not (*this == other); }
    bool operator>=(Self other) const { return other <= *this; }

    Self &operator+=(const Self other) { return this->operator+=(other.value); }
    Self &operator-=(const Self other) { return this->operator-=(other.value); }
    T get_value() const { return value; }

private:
    template<class U>
    T invert_negative(U u) {
        if (u < 0) {
            u += Modulo + Modulo * (-u / Modulo);
        }
        return T(u);
    }
    T value;
};

template <unsigned long long Modulo, class T = unsigned long long>
std::ostream &operator<<(std::ostream &s, const Int<Modulo, T> mi) {
    s << mi.get_value();
    return s;
}

template<size_t Modulo>
struct multiply {
    template <class LHS, class RHS>
    auto operator()(LHS lhs, RHS rhs) const {
        static_assert(is_unsigned<LHS> && is_unsigned<RHS>,
                      "Multiplication routine works with unsigned integers only");
        lhs %= Modulo;
        rhs %= Modulo;
        return (lhs * rhs) % Modulo;
    }
};

template<size_t Modulo>
struct add {
    template<class LHS, class RHS>
    auto operator()(LHS lhs, RHS rhs) const {
        static_assert(is_unsigned<LHS> && is_unsigned<RHS>,
                      "Addition routine works with unsigned integers only");
        lhs %= Modulo;
        rhs %= Modulo;
        return (lhs + rhs) % Modulo;
    }
};

} // namespace modulo
} // namespace olymp
