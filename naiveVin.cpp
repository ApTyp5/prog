//
// Created by arthur on 26.10.2019.
//

#include "naiveVin.h"

Matrix vinogradMult(const Matrix &A, const Matrix &B) {
    if (A.getWid() != B.getLen()) throw "bad sizes";
    size_t M = A.getLen();
    size_t N = A.getWid();
    size_t Q = B.getWid();
    Matrix C(M, Q);

    auto *rawPart = new double[M];
    auto *colPart = new double[Q];
    // Init raw part of substraction
    for (size_t i = 0; i < M; i++) {
        rawPart[i] = 0;
        for (size_t j = 1; j < N; j += 2)
            rawPart[i] -= A[i][j - 1] * A[i][j];
    }

    // Init column part of substraction
    for (size_t j = 0; j < Q; j++) {
        colPart[j] = 0;
        for (size_t i = 1; i < N; i += 2)
            colPart[j] -= B[i][j] * B[i - 1][j];
    }

    // Major cycle
    for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < Q; j++){
            C[i][j] = rawPart[i] + colPart[j];
            for (size_t k = 1; k < N; k += 2)
                C[i][j] += (A[i][k - 1] + B[k][j]) *
                           (B[k - 1][j] + A[i][k]);
        }

    // Catching the accident of non-even N
    if (N%2)
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < Q; j++)
                C[i][j] = C[i][j] + A[i][N - 1] * B[N - 1][j];

    delete [] rawPart;
    delete [] colPart;
    return C;
}