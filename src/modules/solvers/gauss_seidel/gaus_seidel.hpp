// src/modules/solvers/gauss_seidel/gauss_seidel.hpp
#pragma once

#include "../matrix/matrix.hpp"

namespace matrix_project {
namespace solvers {

template<typename T, size_t N, size_t M>
void gauss_seidel(Matrix<T, N, M>& A, Matrix<T, N, 1>& b,
                Matrix<T, N, 1>& x, double tolerance, size_t max_iter) {
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

    Matrix<T, N, M> LUD(L + U + D);
    Matrix<T, N, 1> b_temp(b);

    size_t iter = 0;
    while (norm(b_temp) > tolerance && iter < max_iter) {
        b_temp = b - A * x;
        for (size_t i = 0; i < N; ++i) {
            T sum = 0.0;
            for (size_t k = 0; k < N; ++k) {
                if (k < i) {
                    sum += A(i, k) * x(k);
                } else {
                    sum -= A(i, k) * x[k];
                }
            }
            x[i] = (b[i] - sum) / A(i, i);
        }

        b_temp = b - A * x;

        ++iter;
    }
}

}  // namespace solvers
}  // namespace matrix_project