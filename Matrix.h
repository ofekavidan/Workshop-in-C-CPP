// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows, cols;
} matrix_dims;

class Matrix {
private:
    int rows, cols;
    float * mat;
public:
    // all documentation is in Matrix.cpp (i didn't want to get over 50 lines)
    Matrix(int rows, int cols);
    Matrix();
    Matrix(const Matrix& rhs);
    ~Matrix();
    int get_rows() const;
    int get_cols() const;
    Matrix& transpose();
    Matrix& vectorize();
    void plain_print() const;
    Matrix dot(const Matrix& rhs) const;
    float norm() const;
    Matrix& operator=(const Matrix& rhs);
    Matrix operator+(const Matrix& rhs);
    Matrix operator+(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs);
    Matrix operator*(const Matrix& rhs) const;
    Matrix operator*(float scalar) const;
    friend Matrix operator*(float scalar, const Matrix &m);
    Matrix& operator+=(const Matrix& rhs);
    float& operator()(const int & i, const int & j);
    const float& operator()(const int & i, const int & j) const;
    float& operator[](const int & i);
    const float& operator[](const int & i) const;
    friend std::ostream& operator<< (std::ostream &os, const Matrix& rhs);
    friend std::istream& operator>> (std::istream &in, const Matrix& rhs);
};


#endif //MATRIX_H