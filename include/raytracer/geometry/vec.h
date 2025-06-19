#ifndef VEC_H
#define VEC_H

#include <cmath>

namespace vec {

    // Forward decalre Vec to enable usage in VecBase ctor
    template<typename T, size_t N>
    struct Vec;

namespace detail {

// Internal base class — not part of the public API
template <typename T, size_t N, typename Derived>
struct VecBase {
    static_assert(std::is_arithmetic_v<T>, "T must be a numeric type");

    // Constructors
    // Default constructor
    constexpr VecBase() noexcept = default;
    // Fill constructor
    constexpr explicit VecBase(T value) noexcept {
        for (size_t i = 0; i < N; ++i)
            (*this)[i] = value;
    }
    // Composed constructor
    template <size_t M, typename... Args>
    requires (N == M + sizeof...(Args)) && (std::is_convertible_v<Args, T> && ...)
    constexpr VecBase(const vec::Vec<T, M>& vec, const Args&... args) noexcept {
        T temp[] = { static_cast<T>(args)... };

        // Copy M elements from the input vector
        for (size_t i = 0; i < M; ++i)
            (*this)[i] = vec[i];

        // Copy the remaining Args into the rest
        for (size_t i = 0; i < sizeof...(Args); ++i)
            (*this)[M + i] = temp[i];
    }

    // Convert constructor
    template <size_t M>
    constexpr explicit VecBase(const vec::Vec<T, M>& vec) noexcept {
        for (size_t i = 0; i < N; ++i)
            (*this)[i] = (i < M) ? vec[i] : T{};
    }

    constexpr T& operator[](size_t i) noexcept {
        return static_cast<Derived*>(this)->data[i];
    }

    constexpr const T& operator[](size_t i) const noexcept {
        return static_cast<const Derived*>(this)->data[i];
    }

    constexpr Derived& operator+=(const Derived& other) noexcept {
        for (size_t i = 0; i < N; ++i)
            (*this)[i] += other[i];
        return static_cast<Derived&>(*this);
    }

    constexpr Derived& operator-=(const Derived& other) noexcept {
        for (size_t i = 0; i < N; ++i)
            (*this)[i] -= other[i];
        return static_cast<Derived&>(*this);
    }

    constexpr Derived& operator*=(T scalar) noexcept {
        for (size_t i = 0; i < N; ++i)
            (*this)[i] *= scalar;
        return static_cast<Derived&>(*this);
    }

    constexpr Derived operator+(const Derived& other) const noexcept {
        Derived result = static_cast<const Derived&>(*this);
        result += other;
        return result;
    }

    constexpr Derived operator-(const Derived& other) const noexcept {
        Derived result = static_cast<const Derived&>(*this);
        result -= other;
        return result;
    }

    constexpr Derived operator-() const noexcept {
        Derived result;
        for (size_t i = 0; i < N; ++i)
            result[i] = -(*this)[i];
        return result;
    }

    constexpr Derived operator*(T scalar) const noexcept {
        Derived result = static_cast<const Derived&>(*this);
        result *= scalar;
        return result;
    }

    constexpr friend Derived operator*(T scalar, const Derived& vec) noexcept {
        Derived result;
        for (size_t i = 0; i < N; ++i)
            result[i] = scalar * vec[i];
        return result;
    }

    constexpr friend bool operator==(const Derived& a, const Derived& b) noexcept {
        for (size_t i = 0; i < N; ++i)
            if (a[i] != b[i]) return false;
        return true;
    }

    constexpr friend bool operator!=(const Derived& a, const Derived& b) noexcept {
        return !(a == b);
    }

    constexpr T dot(const Derived& other) const noexcept {
        T sum = 0;
        for (size_t i = 0; i < N; ++i)
            sum += (*this)[i] * other[i];
        return sum;
    }

    // std::sqrt is not constexpr until C++26.
    T length() const noexcept {
        return std::sqrt(dot(static_cast<const Derived&>(*this)));
    }

    constexpr Derived& normalize() noexcept {
        T len = length();
        if (len > T(0))
            *this *= (T(1) / len);
        return static_cast<Derived&>(*this);
    }

    constexpr Derived normalized() const noexcept {
        Derived result = static_cast<const Derived&>(*this);
        return result.normalize();
    }
};

} // namespace detail

// Generic Vec
template<typename T, size_t N>
struct Vec : detail::VecBase<T, N, Vec<T, N>> {
    T data[N];

    using detail::VecBase<T, N, Vec<T, N>>::VecBase;

    constexpr Vec() noexcept : data{} {}

    template<typename... Args>
    requires (sizeof...(Args) == N)
    constexpr explicit Vec(Args... args) noexcept : data{ static_cast<T>(args)... } {}
};

// Specialization
// Vec2
template<typename T>
struct Vec<T, 2> : detail::VecBase<T, 2, Vec<T, 2>> {
    union {
        struct { T x, y; };
        T data[2];
    };

    using detail::VecBase<T, 2, Vec<T, 2>>::VecBase;

    constexpr Vec() noexcept : x(0), y(0) {}
    constexpr Vec(T _x, T _y) noexcept : x(_x), y(_y) {}

    template <size_t M>
    requires (M >= 2)
    constexpr explicit Vec(const Vec<T, M>& vec) noexcept : x(vec[0]), y(vec[1]) {}
};

// Vec3
template<typename T>
struct Vec<T, 3> : detail::VecBase<T, 3, Vec<T, 3>> {
    union {
        struct { T x, y, z; };
        T data[3];
    };

    using detail::VecBase<T, 3, Vec<T, 3>>::VecBase;

    constexpr Vec() noexcept : x(0), y(0), z(0) {}
    constexpr Vec(T _x, T _y, T _z) noexcept : x(_x), y(_y), z(_z) {}
    
    constexpr Vec(Vec<T, 2> vec, T _z) noexcept : x(vec.x), y(vec.y), z(_z) {}

    template <size_t M>
    requires (M >= 3)
    constexpr explicit Vec(const Vec<T, M>& vec) noexcept : x(vec[0]), y(vec[1]), z(vec[2]) {}

    constexpr Vec cross(const Vec& other) const noexcept {
        return Vec(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
};

// Aliases
using Vec2 = Vec<float, 2>;
using Vec3 = Vec<float, 3>;
using Vec4 = Vec<float, 4>;

} // namespace vec

#endif