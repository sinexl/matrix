#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#include "concepts.hpp"

template <MatrixLike A, MatrixLike B>
    requires SameDimensions<A, B>
constexpr auto operator+(const A& a, const B& b)
{
    constexpr int Rows = A::height;
    constexpr int Columns = A::length;
    using Type = typename A::ValueType;

    Matrix<Rows, Columns, Type> result {};
    for (size_t y = 0; y < Rows; ++y)
        for (size_t x = 0; x < Columns; ++x)
            result[y, x] = a[y, x] + b[y, x];
    return result;
}

template <MatrixLike A, MatrixLike B>
    requires SameDimensions<A, B>
constexpr auto operator+=(A& a, const B& b)
{
    constexpr int Rows = A::height;
    constexpr int Columns = A::length;

    for (size_t y = 0; y < Rows; ++y)
        for (size_t x = 0; x < Columns; ++x)
            a[y, x] += b[y, x];
}

template <MatrixLike M, typename Scalar>
constexpr auto operator*(const M& matrix, Scalar scalar)
{
    constexpr int Rows = M::height;
    constexpr int Columns = M::length;
    using Type = typename M::ValueType;
    Matrix<Rows, Columns, Type> result {};

    for (size_t y = 0; y < Rows; ++y)
        for (size_t x = 0; x < Columns; ++x)
            result[y, x] = matrix[y, x] * scalar;

    return result;
}

#endif // OPERATIONS_H_
