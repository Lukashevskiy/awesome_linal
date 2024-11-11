// src/modules/solvers/simple_iteration/simple_iteration.hpp
#pragma once

#include "../matrix/matrix.hpp"

namespace matrix_project {
namespace solvers {

template<typename T, size_t N, size_t M>
void simple_iteration(Matrix<T, N, M>& A, Matrix<T, N, 1>& b,
                    Matrix<T, N, 1>& x, double tolerance, size_t max_iter) {
    Matrix<T, N, 1> x_new(x);
    Matrix<T, N, 1> r(b - A * x);
    Matrix<T, N, N> L(A);
    Matrix<T, N, N> U(A);
    Matrix<T, N, N> D(A);

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < i; ++j) {
            L(i, j) = A(i, j);
            U(j, i) = 0;
        }
        for (size_t j = i; j < N; ++j) {
            L(i, j) = 0;
            U(i, j) = A(i, j);
        }
        D(i, i) = A(i, i);
    }

    Matrix<T, N, N> inv_D = inverse(D);
    Matrix<T, N, N> B = -(inv_D * (L + U));
    Matrix<T, N, 1> c = inv_D * b;

    size_t iter = 0;
    while (norm(r) > tolerance && iter < max_iter) {
        x_new = B * x + c;
        r = b - A * x_new;
        x = x_new;
        ++iter;
    }
}

}  // namespace solvers
}  // namespace matrix_project