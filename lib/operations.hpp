#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#include "concepts.hpp"
#include <concepts>
#include <iostream>

template <MatrixLike A, MatrixLike B>
    requires SameDimensions<A, B>
constexpr auto operator+(const A& a, const B& b)
{
    constexpr int Rows = A::height;
    constexpr int Columns = A::length;
    using Type = decltype(std::declval<typename A::ValueType>() +
                               std::declval<typename B::ValueType>());

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

template <MatrixLike A, MatrixLike B>
    requires ComfortableForMultiplication<A, B>
constexpr auto operator*(const A& a, const B& b) {
    constexpr int Rows = A::height;
    constexpr int Columns = B::length;
    using Type = decltype(std::declval<typename A::ValueType>() +
                               std::declval<typename B::ValueType>());

    Matrix<Rows, Columns, Type> result {};

    for (size_t y = 0; y < Rows; y++) {
        for (size_t x = 0; x < Columns; x++) {
            for (size_t i = 0; i < Rows; ++i) {
                result[y, x] += a[y, i] * b[i, x];
            }
        }
    }

    return result;
}

template <MatrixLike M, typename Scalar>
requires (!MatrixLike<Scalar>)
constexpr auto operator*(const M& matrix, Scalar scalar)
{
    constexpr int Rows = M::height;
    constexpr int Columns = M::length;
    using Type = decltype(std::declval<typename M::ValueType>() *
                               std::declval<Scalar>());
    Matrix<Rows, Columns, Type> result {};

    for (size_t y = 0; y < Rows; ++y)
        for (size_t x = 0; x < Columns; ++x)
            result[y, x] = matrix[y, x] * scalar;

    return result;
}

template <MatrixLike A, MatrixLike B>
requires SameDimensions<A, B> && requires(const typename A::ValueType& x, const typename B::ValueType& y) {
    { x == y } -> std::convertible_to<bool>;
}
constexpr bool operator==(const A& a, const B& b) {
    for (size_t y = 0; y < A::height; y++)
        for (size_t x = 0; x < A::length; x++)
            if (a[y, x] != b[y, x]) return false;
    return true;
}

#endif // OPERATIONS_H_
