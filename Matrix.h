//
// Created by arthur on 26.10.2019.
//

#ifndef PROG_MATRIX_H
#define PROG_MATRIX_H

#include <cstdlib>
#include <string>

class Matrix {
    class Raw {
        double *arr_ptr;
        Raw(double *raw):arr_ptr(raw){}
        //friend class Matrix;
        friend class Matrix;
    public:
        double &operator[](size_t col) const {return arr_ptr[col];}
//        double operator[](size_t col) const { return arr_ptr[col];}
    };

    size_t len;
    size_t wid;
    double *arr;

public:
    Matrix(size_t len, size_t wid);
    Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix) noexcept;
    Matrix& operator=(Matrix const &matrix);
    ~Matrix();

    Raw operator[](size_t raw);
    const Raw operator[](size_t raw) const;

    void fill(double val = 0);
    bool is_eq(const Matrix &mtr) const;
    void print() const;

    size_t getLen() const;
    void setLen(size_t newLen);
    size_t getWid() const;
    void setWid(size_t newWid);

    void show(const std::string& mes);
};

#endif //PROG_MATRIX_H
