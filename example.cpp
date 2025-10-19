#include "lib/concepts.hpp"
#include "lib/operations.hpp"
#include <iostream>

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
    constexpr auto o = Matrix<2, 2>();

    simple_print(o);

    constexpr auto a = Matrix<2, 3> {
        { 1, 2, 3 },
        { 4, 5, 6 },
    };
    simple_print((a + a) * 10);
}
