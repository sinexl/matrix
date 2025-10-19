#ifndef MATRIX_H_
#define MATRIX_H_


#include <cstddef>
#include <type_traits>
#include <utility>

template <int Rows, int Columns, typename Type = int>
struct BasicMatrix {
    static constexpr int height = Rows;
    static constexpr int length = Columns;
    using ValueType = Type;

    constexpr decltype(auto) operator[](this auto&& self, size_t row, size_t column)
    {
        return std::remove_cvref_t<decltype(self)>::index(std::forward<decltype(self)>(self), row, column);
    }
};


template <int Rows, int Columns, typename Type = int>
struct Matrix : BasicMatrix<Rows, Columns, Type> {
    Type data[Rows][Columns];

    static constexpr decltype(auto) index(auto&& self, size_t row, size_t column)
    {
        return std::forward<decltype(self)>(self).data[row][column];
    }

    constexpr Matrix(std::initializer_list<std::initializer_list<Type>> initializer)
    {

        // TODO: Add some sort of check whether the user initializes all of elements or not
        size_t i = 0;
        for (const auto& row : initializer) {
            size_t j = 0;
            for (const Type& val : row) {
                data[i][j] = val;
                ++j;
            }
            ++i;
        }
    }

    // If you need zero-filled matrix, it is recommended to use ZeroMatrix class that doesn't allocate any memory.
    constexpr Matrix()
    {
        // TODO: For some curious reason, std::fill doesnt work on constexpr
        for (size_t i = 0; i < Rows; ++i)
            for (size_t j = 0; j < Columns; ++j)
                data[i][j] = Type {};
    }
};

template <int N, typename Type = int>
struct IdentityMatrix : BasicMatrix<N, N, Type> {
    constexpr static Type index(auto&&, [[maybe_unused]] size_t row, [[maybe_unused]] size_t column)
    {
        return row == column ? Type { 1 } : Type { 0 };
    }
};

template <int Rows, int Columns, typename Type = int>
struct ZeroMatrix : BasicMatrix<Rows, Columns, Type> {
    constexpr static Type index(auto&&, [[maybe_unused]] size_t row, [[maybe_unused]] size_t column)
    {
        return Type { 0 }; // TODO: option to add useless (in this scenario) bound check,
                           // Currently, ZeroMatrix<1>{}[1000, 1000] will work.
    }
};

#endif // MATRIX_H_
