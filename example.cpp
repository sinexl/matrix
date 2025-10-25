#include "lib/concepts.hpp"
#include "lib/operations.hpp"
#include <cassert>
#include <iostream>
using namespace std;

template <MatrixLike M>
constexpr void simple_print(const M& matrix)
{
    using std::cout;
    using std::endl;
    for (int y = 0; y < matrix.height; y++) {
        for (int x = 0; x < matrix.length; x++)
            cout << matrix[y, x] << " ";
        cout << endl;
    }
}

int main()
{
    constexpr auto a = Matrix<3, 2> {
        { 1, 2 },
        { 3, 4 },
        { 5, 6 },
    };
    constexpr auto b = Matrix<2, 3> {
        { 7, 8, 9 },
        { 10, 11, 12 },
    };

    constexpr auto c = a * b;
    simple_print(c);
    cout << " ----- " << endl;
    simple_print(transpose(Matrix<3, 2>{{1, 2}, {3, 4}, {5, 6}}));
    assert(transpose(transpose(c)) == c);
}
