//
// Created by arthur on 26.10.2019.
//
#include <thread>
#include "parallelVin.h"

double *initRawPart(const Matrix &A, size_t M, size_t N);
double *initColPart(const Matrix &B, size_t Q, size_t N);
void majorMultCycle(Matrix &C, const Matrix &A, const Matrix &B,
                    size_t M, size_t N, size_t Q,
                    size_t n_threads);


Matrix parVinogradMult(const Matrix &A, const Matrix &B, const size_t n_threads){
    using namespace std;

    if (A.getWid() != B.getLen()) throw "bad sizes";
    size_t M = A.getLen();
    size_t N = A.getWid();
    size_t Q = B.getWid();
    Matrix C(M, Q);

    double *rawPart = nullptr;
    double *colPart = nullptr;

    thread rawInitThread([&](){
        rawPart = initRawPart(A, M, N);
    });

    thread colInitThread([&](){
        colPart = initColPart(B, Q, N);
    });

    if (rawInitThread.joinable()) rawInitThread.join();
    if (colInitThread.joinable()) colInitThread.join();

    auto majorCycle = [&](size_t start){
        for (size_t i = start; i < M; i += n_threads) {
            for (size_t j = 0; j < Q; j++) {
                C[i][j] = rawPart[i] + colPart[j];
                for (size_t k = 1; k < N; k += 2)
                    C[i][j] += (A[i][k - 1] + B[k][j]) *
                               (B[k - 1][j] + A[i][k]);
            }
        }
    };

    auto *threads = new thread [n_threads];
    for (size_t i = 0; i < n_threads; i++)
        threads[i] = thread(majorCycle, i);

    for (size_t i = 0; i < n_threads; i++)
        if (threads[i].joinable()) threads[i].join();

    // Catching the accident of non-even N
    if (N%2)
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < Q; j++)
                C[i][j] = C[i][j] + A[i][N - 1] * B[N - 1][j];

    delete [] rawPart;
    delete [] colPart;
    delete [] threads;
    return C;
}

double *initRawPart(const Matrix &A, size_t M, size_t N){
    auto *rawPart = new double[M];
    for (size_t i = 0; i < M; i++){
        rawPart[i] = 0;
        for (size_t j = 1; j < N; j += 2)
            rawPart[i] -= A[i][j - 1] * A[i][j];
    }

    return rawPart;
}

double *initColPart(const Matrix &B, size_t Q, size_t N){
    auto *colPart = new double[Q];
    for (size_t j = 0; j < Q; j++) {
        colPart[j] = 0;
        for (size_t i = 1; i < N; i += 2)
            colPart[j] -= B[i][j] * B[i - 1][j];
    }

    return colPart;
}