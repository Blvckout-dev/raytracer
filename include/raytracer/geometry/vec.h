#ifndef VEC_H
#define VEC_H

#include <array>
#include <cmath>

// Generic N-dimensional Vec
template <typename Derived, typename T, size_t N>
struct VecBase {
    std::array<T, N> data{};
    
    // Constructor
    VecBase() = default;

    template<typename... Args>
    VecBase(Args... args) {
        static_assert(sizeof...(args) == N, "Incorrect number of arguments");

        // Use initializer list to fill the array with arguments
        data = {static_cast<T>(args)...};
    }

    Derived& self() { return static_cast<Derived&>(*this); }
    const Derived& self() const { return static_cast<const Derived&>(*this); }

    T& operator[](size_t i) { return data[i]; }
    T operator[](size_t i) const { return data[i]; }

    // In-place addition
    Derived& operator+=(const Derived& other) const {
        for (size_t i = 0; i < N; ++i)
            data[i] += other[i];
        return self();
    }

    Derived& operator-=(const Derived& other) {
        for (size_t i = 0; i < N; ++i)
            data[i] -= other[i];
        return self();
    }

    Derived& operator*=(T scalar) {
        for (size_t i = 0; i < N; ++i)
            data[i] *= scalar;
        return self();
    }

    Derived operator+(const Derived& other) const {
        Derived result;
        for (size_t i = 0; i < N; ++i)
            result[i] = data[i] + other[i];
        return result;
    }

    Derived operator-() const {
        Derived result = self();
        for (size_t i = 0; i < N; ++i)
            result[i] = -data[i];
        return result;
    }

    Derived operator-(const Derived& other) const {
        Derived result = self();
        result -= other;
        return result;
    }

    Derived operator*(T scalar) const {
        Derived result = self();
        result *= scalar;
        return result;
    }

    T dot(const Derived& other) const {
        T sum = 0.0f;
        for (size_t i = 0; i < N; ++i)
            sum += data[i] * other[i];
        return sum;
    }

    T length() const {
        return std::sqrt(dot(self()));
    }

    Derived& normalize() {
        T len = length();
        if (len > 0.0f)
            *this *= (1.0f / len);
        return self();
    }

    Derived normalized() const {
        Derived result = self();
        return result.normalize();
    }
};

// Inherit vec base
template<typename T, size_t N>
struct Vec : public VecBase<Vec<T, N>, T, N> {
    // Constructor
    using VecBase<Vec<T, N>, T, N>::VecBase;
};

// Specialization 
template<typename T>
struct Vec<T, 3> : public VecBase<Vec<T, 3>, T, 3> {
    T& x = this->data[0];
    T& y = this->data[1];
    T& z = this->data[2];

    // Constructors
    using VecBase<Vec, T, 3>::VecBase;
    
    Vec(T x_, T y_, T z_) {
        this->data[0] = x_;
        this->data[1] = y_;
        this->data[2] = z_;
    }
    
    Vec(const Vec<T, 3>& vec) {
        this->data[0] = vec.x;
        this->data[1] = vec.y;
        this->data[2] = vec.z;
    }

    Vec<T, 3>& operator=(const Vec<T, 3>& other) {
        if (this != &other) { // Prevent self-assignment
            this->data[0] = other.data[0];
            this->data[1] = other.data[1];
            this->data[2] = other.data[2];
        }
        return *this;
    }
    
    Vec<T, 3> cross(const Vec<T, 3>& other) const {
        return Vec<T, 3>{
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }
};

// Aliases
using Vec2 = Vec<float, 2>;
using Vec3 = Vec<float, 3>;
using Vec4 = Vec<float, 4>;

#endif