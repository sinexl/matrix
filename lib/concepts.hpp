#ifndef CONCEPTS_H_
#define CONCEPTS_H_
#include <concepts>
#include "matrix.hpp"

/// Base concept for all matrix types.
/// Requires the type to derive from BasicMatrix with matching dimensions and value type.
/// Should be used to specify generic matrix type.
template <typename M>
concept MatrixLike = std::derived_from<M, BasicMatrix<M::height, M::length, typename M::ValueType>>;

/// Ensures the dimension equality of Matrices.
template <typename A, typename B>
concept SameDimensions =
    MatrixLike<A> && MatrixLike<B> &&
    (A::height == B::height) && (A::length == B::length);

template <typename M>
concept SquareMatrix = MatrixLike<M> && (M::height == M::length);
template <typename M>
concept RowMatrix = MatrixLike<M> && (M::height == 1);
template <typename M>
concept ColumnMatrix = MatrixLike<M> && (M::length == 1);

#endif // CONCEPTS_H_
