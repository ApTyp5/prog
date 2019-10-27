#include <iostream>
#include <fstream>
#include <chrono>

#include "naiveVin.h"
#include "parallelVin.h"

void make_experiment(size_t start, size_t stop, size_t step,
                     size_t start_threads, size_t stop_threads);

int main() {
    make_experiment(100, 1001, 100,
                    4096*2, 10000);

    return 0;
}

void make_experiment(size_t start, size_t stop, size_t step,
                     size_t start_threads, size_t stop_threads) {
    using namespace std::chrono;

    std::ofstream fout;
    std::string fnam = "common.exp";
    fout.open(fnam);

    for (size_t size = start; size < stop; size += step){
        Matrix A(size, size), B(A), C(A);

        auto begin = high_resolution_clock::now();
        C = vinogradMult(A, B);
        auto end = high_resolution_clock::now();
        auto dur = duration_cast<microseconds>(end - begin).count();

        fout << size << "\t" << dur << std::endl;

        std::cout << "common: " << size << " size done" << std::endl;
    }
    fout.close();

    for (size_t thread_num = start_threads; thread_num < stop_threads; thread_num *= 2){
        fnam = "thread_" + std::to_string(thread_num) + ".exp";
        fout.open(fnam);

        for (size_t size = start; size < stop; size += step){
            Matrix A(size, size), B(A), C(A);

            auto begin = high_resolution_clock::now();
            C = parVinogradMult(A, B, thread_num);
            auto end = high_resolution_clock::now();
            auto dur = duration_cast<microseconds>(end - begin).count();

            fout << size << "\t" << dur << std::endl;

            std::cout << "parallel: " << thread_num << " threads, " << size << " size done" << std::endl;
        }
        fout.close();
    }
}
