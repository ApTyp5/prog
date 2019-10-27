//
// Created by arthur on 26.10.2019.
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-c-copy-assignment-signature"
//
// Created by arthur on 23.09.2019.
//

#include <iostream>
#include <cstring>
#include "Matrix.h"


Matrix::Matrix(size_t len, size_t wid):len(len), wid(wid), arr(new double[len * wid]) {}

Matrix::~Matrix(){delete [] arr;}

Matrix::Matrix(const Matrix &matrix) {
    this->len = matrix.getLen();
    this->wid = matrix.getWid();
    this->arr = new double [len * wid];
    memcpy(arr, matrix.arr, len * wid * sizeof(double));
}


Matrix::Matrix(Matrix &&matrix) noexcept {
    this->len = matrix.len;
    this->wid = matrix.wid;
    this->arr = matrix.arr;
    matrix.arr = nullptr;
}

Matrix &Matrix::operator=(const Matrix &matrix) {
    Matrix *mtr = new Matrix(matrix);
    return *mtr;
}

size_t Matrix::getLen() const {
    return len;
}

void Matrix::setLen(size_t newLen) {
    Matrix::len = newLen;
}

size_t Matrix::getWid() const {
    return wid;
}

void Matrix::setWid(size_t newWid) {
    Matrix::wid = newWid;
}

Matrix::Raw Matrix::operator[](size_t raw) {
    return Raw(arr + raw * wid);
}

void Matrix::fill(double val) {
    for (size_t i = 0; i < len * wid; i++){
        *(arr + i) = val;
    }
}

const Matrix::Raw Matrix::operator[](size_t raw) const {
    return Raw(arr + raw * wid);
}

bool Matrix::is_eq(const Matrix &mtr) const {
    if (mtr.getWid() != wid ||
        mtr.getLen() != len)
        return false;
    for (size_t i = 0; i < len; i++)
        for (size_t j = 0; j < wid; j++)
            if (abs(operator[](i)[j] - mtr[i][j]) > 1e-6)
                return false;
    return  true;
}

void Matrix::print() const {
    std::cout << "\n";

    for (size_t i = 0; i < len; i++){
        for (size_t j = 0; j < wid; j++){
            std::cout << operator[](i)[j] << "\t";
        }
        std::cout << "\n";
    }
}

void Matrix::show(const std::string& mes = "") {
    std::cout << mes << std::endl;
    for (size_t i = 0; i < len; i++){
        for (size_t j = 0; j < wid; j++){
            std::cout << (*this)[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


#pragma clang diagnostic pop
