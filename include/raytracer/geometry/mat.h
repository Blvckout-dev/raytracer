#ifndef MAT_H
#define MAT_H

#include "vec.h"
#include <array>
#include <cmath>
#include <type_traits>
#include <iostream>
#include <iomanip>

using vec::Vec;

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

    constexpr Mat inversed() const requires (C == 3 && R == 3) {
        const Mat& m = *this;

        T det =
            m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
            - m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
            + m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);

        T invDet = T{1} / det;

        Mat inv;

        inv[0][0] =  (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invDet;
        inv[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * invDet;
        inv[2][0] =  (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invDet;

        inv[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * invDet;
        inv[1][1] =  (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * invDet;
        inv[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * invDet;

        inv[0][2] =  (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * invDet;
        inv[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * invDet;
        inv[2][2] =  (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invDet;

        return inv;
    }

    constexpr Mat inversed() const requires (C == 4 && R == 4) {
        const Mat& m = *this;

        // Compute cofactors for each element (hardcoded for 4x4)
        T cof00 =  m[1][1] * (m[2][2]*m[3][3] - m[3][2]*m[2][3])
                - m[2][1] * (m[1][2]*m[3][3] - m[3][2]*m[1][3])
                + m[3][1] * (m[1][2]*m[2][3] - m[2][2]*m[1][3]);

        T cof01 = - (m[1][0] * (m[2][2]*m[3][3] - m[3][2]*m[2][3])
                - m[2][0] * (m[1][2]*m[3][3] - m[3][2]*m[1][3])
                + m[3][0] * (m[1][2]*m[2][3] - m[2][2]*m[1][3]));

        T cof02 =  m[1][0] * (m[2][1]*m[3][3] - m[3][1]*m[2][3])
                - m[2][0] * (m[1][1]*m[3][3] - m[3][1]*m[1][3])
                + m[3][0] * (m[1][1]*m[2][3] - m[2][1]*m[1][3]);

        T cof03 = - (m[1][0] * (m[2][1]*m[3][2] - m[3][1]*m[2][2])
                - m[2][0] * (m[1][1]*m[3][2] - m[3][1]*m[1][2])
                + m[3][0] * (m[1][1]*m[2][2] - m[2][1]*m[1][2]));

        // Compute determinant (dot product of first row and cofactors)
        T det = m[0][0] * cof00 + m[0][1] * cof01 + m[0][2] * cof02 + m[0][3] * cof03;

        // No zero check for det here (caller must ensure invertible)
        T invDet = T{1} / det;

        Mat inv{};

        inv[0][0] = cof00 * invDet;
        inv[1][0] = cof01 * invDet;
        inv[2][0] = cof02 * invDet;
        inv[3][0] = cof03 * invDet;

        // Repeat for remaining cofactors (you can calculate each as above)
        inv[0][1] = - (m[0][1] * (m[2][2]*m[3][3] - m[3][2]*m[2][3])
                    - m[2][1] * (m[0][2]*m[3][3] - m[3][2]*m[0][3])
                    + m[3][1] * (m[0][2]*m[2][3] - m[2][2]*m[0][3])) * invDet;

        inv[1][1] =   (m[0][0] * (m[2][2]*m[3][3] - m[3][2]*m[2][3])
                    - m[2][0] * (m[0][2]*m[3][3] - m[3][2]*m[0][3])
                    + m[3][0] * (m[0][2]*m[2][3] - m[2][2]*m[0][3])) * invDet;

        inv[2][1] = - (m[0][0] * (m[2][1]*m[3][3] - m[3][1]*m[2][3])
                    - m[2][0] * (m[0][1]*m[3][3] - m[3][1]*m[0][3])
                    + m[3][0] * (m[0][1]*m[2][3] - m[2][1]*m[0][3])) * invDet;

        inv[3][1] =   (m[0][0] * (m[2][1]*m[3][2] - m[3][1]*m[2][2])
                    - m[2][0] * (m[0][1]*m[3][2] - m[3][1]*m[0][2])
                    + m[3][0] * (m[0][1]*m[2][2] - m[2][1]*m[0][2])) * invDet;

        inv[0][2] =   (m[0][1] * (m[1][2]*m[3][3] - m[3][2]*m[1][3])
                    - m[1][1] * (m[0][2]*m[3][3] - m[3][2]*m[0][3])
                    + m[3][1] * (m[0][2]*m[1][3] - m[1][2]*m[0][3])) * invDet;

        inv[1][2] = - (m[0][0] * (m[1][2]*m[3][3] - m[3][2]*m[1][3])
                    - m[1][0] * (m[0][2]*m[3][3] - m[3][2]*m[0][3])
                    + m[3][0] * (m[0][2]*m[1][3] - m[1][2]*m[0][3])) * invDet;

        inv[2][2] =   (m[0][0] * (m[1][1]*m[3][3] - m[3][1]*m[1][3])
                    - m[1][0] * (m[0][1]*m[3][3] - m[3][1]*m[0][3])
                    + m[3][0] * (m[0][1]*m[1][3] - m[1][1]*m[0][3])) * invDet;

        inv[3][2] = - (m[0][0] * (m[1][1]*m[3][2] - m[3][1]*m[1][2])
                    - m[1][0] * (m[0][1]*m[3][2] - m[3][1]*m[0][2])
                    + m[3][0] * (m[0][1]*m[1][2] - m[1][1]*m[0][2])) * invDet;

        inv[0][3] = - (m[0][1] * (m[1][2]*m[2][3] - m[2][2]*m[1][3])
                    - m[1][1] * (m[0][2]*m[2][3] - m[2][2]*m[0][3])
                    + m[2][1] * (m[0][2]*m[1][3] - m[1][2]*m[0][3])) * invDet;

        inv[1][3] =   (m[0][0] * (m[1][2]*m[2][3] - m[2][2]*m[1][3])
                    - m[1][0] * (m[0][2]*m[2][3] - m[2][2]*m[0][3])
                    + m[2][0] * (m[0][2]*m[1][3] - m[1][2]*m[0][3])) * invDet;

        inv[2][3] = - (m[0][0] * (m[1][1]*m[2][3] - m[2][1]*m[1][3])
                    - m[1][0] * (m[0][1]*m[2][3] - m[2][1]*m[0][3])
                    + m[2][0] * (m[0][1]*m[1][3] - m[1][1]*m[0][3])) * invDet;

        inv[3][3] =   (m[0][0] * (m[1][1]*m[2][2] - m[2][1]*m[1][2])
                    - m[1][0] * (m[0][1]*m[2][2] - m[2][1]*m[0][2])
                    + m[2][0] * (m[0][1]*m[1][2] - m[1][1]*m[0][2])) * invDet;

        return inv;
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