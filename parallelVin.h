//
// Created by arthur on 26.10.2019.
//

#ifndef PROG_PARALLELVIN_H
#define PROG_PARALLELVIN_H

#include "Matrix.h"

Matrix parVinogradMult(const Matrix &A, const Matrix &B, size_t thread_num = 4);

#endif //PROG_PARALLELVIN_H
