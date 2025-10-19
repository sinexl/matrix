#include <concepts>
#include <cstring>
#include <iostream>
#include <utility>

using std::cout;
using std::endl;

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

template <typename M>
concept MatrixLike =
    std::derived_from<M, BasicMatrix<M::height, M::length, typename M::ValueType>>;

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
    constexpr Matrix() {
        // TODO: For some curious reason, std::fill doesnt work on constexpr
        for (size_t i = 0; i < Rows; ++i)
            for (size_t j = 0; j < Columns; ++j)
                data[i][j] = Type{};
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



template <MatrixLike A, MatrixLike B>
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

template <MatrixLike M>
constexpr void simple_print(const M& matrix)
{
    for (int y = 0; y < matrix.height; y++) {
        for (int x = 0; x < matrix.length; x++)
            cout << matrix[y, x] << " ";
        cout << endl;
    }
}

int main()
{
    constexpr auto o = Matrix<2, 2>();

    simple_print(o);

    constexpr auto a = Matrix<2, 3> {
        { 1, 2, 3 },
        { 4, 5, 6 },
    };
    simple_print((a + a) * 10);

    // constexpr auto a = Matrix<2, 2, float> {
    //     { 1, 2 },
    //     { 3, 4 },
    // };
}
