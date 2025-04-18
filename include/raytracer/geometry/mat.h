#ifndef MAT_H
#define MAT_H

#include "vec.h"
#include <array>
#include <cmath>
#include <type_traits>
#include <iostream>
#include <iomanip>

template<typename T, size_t R, size_t C>
struct Mat {
    static_assert(std::is_arithmetic_v<T>, "T must be a numeric type");

    std::array<Vec<T, R>, C> data{};

    Mat() = default;

    // Static constructor for identity matrix
    static Mat identity() {
        static_assert(C == R, "Identity requires a square matrix");
        Mat m{}; // default initialization
        for (size_t i = 0; i < C; ++i) {
            m[i][i] = T(1);
        }
        return m;
    }

    Vec<T, R>& operator[](size_t col) { return data[col]; }
    const Vec<T, R>& operator[](size_t col) const { return data[col]; }

    T operator()(size_t row, size_t col) const { return data[col][row]; }

    /// @brief Mirrors the matrix along its main diagonal
    /// @return A new matrix of dimensions (C x R)
    Mat transpose() const {
        Mat result{};
        for (size_t i = 0; i < C; ++i)
            for (size_t j = 0; j < R; ++j)
                result[j][i] = data[i][j];
        return result;
    }

    /// @brief Outputs matrix in row-major layout
    void print() const {
        for (size_t row = 0; row < R; ++row) {
            std::cout << "[ ";
            for (size_t col = 0; col < C; ++col) {
                std::cout << std::setw(4) << (*this)(row, col) << " ";
            }
            std::cout << "]\n";
        }
    }
};

/* region Free functions */

/// @brief Multiplies two matrices
/// @tparam T Value type (e.g., float, int)
/// @tparam R Number of rows in `a`
/// @tparam K Shared inner dimension (columns in `a`, rows in `b`)
/// @tparam C Number of columns in `b`
/// @param a Left-hand matrix operand (R x K)
/// @param b Right-hand matrix operand (K x C)
/// @return Matrix product of `a * b`, with dimensions (R x C)
template<typename T, size_t R, size_t K, size_t C>
inline Mat<T, R, C> operator*(const Mat<T, R, K>& a, const Mat<T, K, C>& b) {
    Mat<T, R, C> result{};

    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j < C; ++j) {
            T sum = T(0);
            //Inner dimension (columns of a and rows of b)
            for (size_t k = 0; k < K; ++k) {
                sum += a[k][i] * b[j][k];
            }
            // column-major order
            result[j][i] = sum;
        }
    }

    return result;
}

/// @brief Multiplies a matrix with a column vector
/// @tparam T Value type (e.g., float, int)
/// @tparam R Number of rows in `mat` and size of result column vector
/// @tparam C Size of column vector `vec` and number of columns in `mat`
/// @param mat Left-hand matrix operand (R x C)
/// @param vec Right-hand matrix operand Vec<T, C>
/// @return Resulting column vector (Vec<T, R>) of the matrix-vector multiplication
template<typename T, size_t R, size_t C>
inline Vec<T, R> operator*(const Mat<T, R, C>& mat, const Vec<T, C>& vec) {
    Vec<T, R> result{};
    for (size_t i = 0; i < C; ++i)
        for (size_t j = 0; j < R; ++j)
            result[j] += mat[i][j] * vec[i];
    return result;
}

/// @brief Multiplies a row vector with a matrix
/// @tparam T Value type (e.g., float, int)
/// @tparam R Size of row vector `vec` and number of rows in `mat`
/// @tparam C Number of columns in `mat` and size of result row vector
/// @param vec Left-hand row vector operand Vec<T, R>
/// @param mat Right-hand matrix operand (R x C)
/// @return Resulting row vector (Vec<T, C>) of the matrix-vector multiplication
template<typename T, size_t R, size_t C>
inline Vec<T, C> operator*(const Vec<T, R>& vec, const Mat<T, R, C>& mat) {
    Vec<T, C> result{};
    for (size_t i = 0; i < C; ++i)
        for (size_t j = 0; j < R; ++j)
            result[i] += vec[j] * mat[i][j];
    return result;
}

/* endregion Free functions */

// Aliases
using Mat2 = Mat<float, 2, 2>;
using Mat3 = Mat<float, 3, 3>;
using Mat4 = Mat<float, 4, 4>;

#endif