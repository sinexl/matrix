#include <concepts>
#include <cstring>
#include <iostream>
#include <utility>

using std::cout;
using std::endl;

template <int Rows, int Columns, typename Type = int>
struct MatrixLike {
    static constexpr int height = Rows;
    static constexpr int length = Columns;
    using ValueType = Type;

    constexpr decltype(auto) operator[](this auto&& self, size_t row, size_t column)
    {
        return std::remove_cvref_t<decltype(self)>::index(std::forward<decltype(self)>(self), row, column);
    }
};

template <int Rows, int Columns, typename Type = int>
struct Matrix : MatrixLike<Rows, Columns, Type> {
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

    constexpr Matrix()
    {
        std::fill(&data[0][0], &data[0][0] + Rows * Columns, Type {});
    }
};

template <int N, typename Type = int>
struct IdentityMatrix : MatrixLike<N, N, Type> {
    static Type index(auto&&, [[maybe_unused]] size_t row, [[maybe_unused]] size_t column)
    {
        return row == column ? Type { 1 } : Type { 0 };
    }
};

template <int Rows, int Columns, typename Type = int>
struct ZeroMatrix : MatrixLike<Rows, Columns, Type> {
    constexpr static Type index(auto&&, [[maybe_unused]] size_t row, [[maybe_unused]] size_t column)
    {
        return Type { 0 }; // TODO: option to add useless (in this scenario) bound check,
                           // Currently, ZeroMatrix<1>{}[1000, 1000] will work.
    }
};

template <typename A, typename B>
    requires std::derived_from<A, MatrixLike<A::height, A::length, typename A::ValueType>>
    && std::derived_from<B, MatrixLike<A::height, A::length, typename A::ValueType>>
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

int main()
{
    auto o = Matrix<2, 2> {};
    for (int y = 0; y < o.height; y++) {
        for (int x = 0; x < o.length; x++)
            cout << o[y, x] << " ";
        cout << endl;
    }

    constexpr auto a = Matrix<2, 2> {
        { 1, 2 },
        { 3, 4 },
    };
}
