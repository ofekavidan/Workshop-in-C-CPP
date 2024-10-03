//
// Created by Ofek Avidan on 27/08/2022.
//
#include "Matrix.h"

#include <cmath>

#define THRESHOLD 0.1
#define MINIMAL_ROWS_COLS 0
#define INITIAL_BOOT_MATRIX 1
#define LENGTH_ERROR "length error"
#define OUT_OF_RANGE_ERROR "out of ragne error"
#define RUNTIME_ERROR "runtime error"

/**
 * the constructor. gets the dimensions of rows and cols of the matrix.
 * creates a dynamic memory allocation for rows x cols matrix.
 * then initialize all the elements of the matrix to be 0.
 * @param rows - rows dimension.
 * @param cols - cols dimension.
 */
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    if(rows <= MINIMAL_ROWS_COLS || cols <= MINIMAL_ROWS_COLS)
    {
        throw std::length_error(LENGTH_ERROR);
    }

    mat = new float[rows * cols];

    for (int i = 0; i < cols * rows; ++i) {
        mat[i] = 0;
    }
}

/**
 * our "default" constructor. initialize the matrix to be 1X1 matrix with the
 * element 0.
 */
Matrix::Matrix() : rows(INITIAL_BOOT_MATRIX), cols(INITIAL_BOOT_MATRIX),
                   mat(new float[INITIAL_BOOT_MATRIX]) {
    mat[0] = 0;
}


/**
 * our copy constructor. uses our copy assignment easily.
 * @param m - the matrix we want to get the attributes from.
 */
Matrix::Matrix(const Matrix &m) :rows(),cols(), mat() {
    *this = m;
}

/**
 * our destructor. free the memory from the heap.
 */
Matrix::~Matrix() {
    delete[] mat;
}

/**
 * this function returns the column dimension of the matrix.
 * @return column dimension of the matrix.
 */
int Matrix::get_cols() const {
    return this->cols;
}

/**
 * this function returns the row dimension of the matrix.
 * @return row dimension of the matrix.
 */
int Matrix::get_rows() const {
    return this->rows;
}

/**
 * this function transpose the current matrix.
 * @return the current matrix, but transposed.
 */
Matrix& Matrix::transpose() {
    float *arr = new float[rows * cols];

    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; j++) {
            arr[i * rows + j] = (*this)(j, i);
        }
    }
    delete[] this->mat;
    this->mat = arr;
    int tmp = this->cols;
    this->cols = this->rows;
    this->rows = tmp;
    return *this;
}

/**
 * this function vectorize the current matrix.
 * @return the current matrix, but vectorized.
 */
Matrix& Matrix::vectorize() {
    rows = rows * cols;
    cols = 1;
    return *this;
}

/**
 * this function print every element of the matrix.
 */
void Matrix::plain_print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << mat[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * this function multiply every coordination of two matrices.
 * @param rhs - the "right" matrix.
 * @return "doted" matrix.
 */
Matrix Matrix::dot(const Matrix& rhs) const {
    if (this->cols != rhs.cols || this->rows != rhs.rows) {
        throw std::length_error(LENGTH_ERROR);
    }

    Matrix new_matrix = Matrix(rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        new_matrix[i] = mat[i] * rhs.mat[i];
    }
    return new_matrix;
}

/**
 * this function calculates and returns the norm of the current matrix.
 * @return the norm of the current matrix.
 */
float Matrix::norm() const {
    float sum = 0;
    for (int i = 0; i < rows * cols; ++i) {
        sum += (mat[i]) * (mat[i]);
    }
    return std::sqrt(sum);
}

/**
 * our "copy assignment". gets the "right" matrix which full of attributes,
 * and "full" or update the "left" matrix to these attributes.
 * @param rhs - the "right" matrix.
 * @return the "updated" left matrix.
 */
Matrix &Matrix::operator=(const Matrix &rhs) {

    if(rhs.rows <= MINIMAL_ROWS_COLS || rhs.cols <= MINIMAL_ROWS_COLS)
    {
        throw std::length_error(LENGTH_ERROR);
    }

    if (this == &rhs) {
        return *this;
    }
    delete[] mat;

    rows = rhs.rows;
    cols = rhs.cols;
    mat = new float[rows * cols];

    for (int i = 0; i < rows * cols; ++i) {
        this->mat[i] = rhs.mat[i];
    }
    return *this;
}

/**
 * our plus operator. gets two matrices and calculate the sum of every
 * coordination.
 * @param rhs - the "right" matrix.
 * @return the "summed" and updated matrix.
 */
Matrix Matrix::operator+(const Matrix &rhs) {
    if (this->cols != rhs.cols || this->rows != rhs.rows) {
        throw std::length_error(LENGTH_ERROR);
    }

    Matrix new_matrix = Matrix(rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        new_matrix.mat[i] = mat[i] + rhs.mat[i];
    }
    return new_matrix;
}

/**
 * our plus operator. gets two matrices and calculate the sum of every
 * coordination.
 * @param rhs - the "right" matrix.
 * @return the "summed" and updated matrix.
 */
Matrix Matrix::operator+(const Matrix &rhs) const {
    if (this->cols != rhs.cols || this->rows != rhs.rows) {
        throw std::length_error(LENGTH_ERROR);
    }

    Matrix new_matrix = Matrix(rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        new_matrix.mat[i] = mat[i] + rhs.mat[i];
    }
    return new_matrix;
}

/**
 * our "multiplication matrix" operator.
 * gets two matrices and calculate their multiplication.
 * @param rhs - the "right" matrix.
 * @return the "multiplied" and updated matrix.
 */
Matrix Matrix::operator*(const Matrix &rhs) {
    if (this->cols != rhs.rows) {
        throw std::length_error(LENGTH_ERROR);
    }

    Matrix new_matrix = Matrix(rows, rhs.cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rhs.cols; ++j) {
            float row_multiply_col = 0;
            for (int k = 0; k < cols; ++k) {
                row_multiply_col += (*this)(i, k) * rhs(k, j);
            }
            new_matrix(i,j) = row_multiply_col;
        }
    }
    return new_matrix;
}

/**
 * our "multiplication matrix" operator.
 * gets two matrices and calculate their multiplication.
 * @param rhs - the "right" matrix.
 * @return the "multiplied" and updated matrix.
 */
Matrix Matrix::operator*(const Matrix &rhs) const {
    if (this->cols != rhs.rows) {
        throw std::length_error(LENGTH_ERROR);
    }

    Matrix new_matrix = Matrix(rows, rhs.cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rhs.cols; ++j) {
            float row_multiply_col = 0;
            for (int k = 0; k < cols; ++k) {
                row_multiply_col += (*this)(i, k) * rhs(k, j);
            }
            new_matrix(i,j) = row_multiply_col;
        }
    }
    return new_matrix;
}

/**
 * this function gets a number and multiply the current matrix by the number.
 * @param scalar - the number we want to multiply by
 * @return the "multiplied" and updated matrix.
 */
Matrix Matrix::operator*(float scalar) const {
    Matrix new_matrix = Matrix(rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        new_matrix.mat[i] = mat[i] * scalar;
    }
    return new_matrix;
}

/**
 * this function gets a number and multiply the current matrix by the number.
 * @param scalar - the number we want to multiply by
 * @return the "multiplied" and updated matrix.
 */
Matrix operator*(float scalar, const Matrix &m) {
    return m*scalar;
}

/**
 * the += operator. gets two matrices and calculate the sum of every
 * coordination.
 * @param rhs - the "right" matrix.
 * @return the "summed" and updated matrix.
 */
Matrix& Matrix::operator+=(const Matrix &rhs) {
    *this = *this + rhs;
    return *this;
}

/**
 * the () operator. gets two indexes
 * ints (i,j) and returns the (i,j) coordination
 * of the current matrix.
 * @param i - row index
 * @param j - column index
 * @return the (i,j) coordination
 */
float &Matrix::operator()(const int &i, const int &j) {
    if (i >= rows || j >= cols || i < MINIMAL_ROWS_COLS ||
    j < MINIMAL_ROWS_COLS) {
        throw std::out_of_range(OUT_OF_RANGE_ERROR);
    }
    return mat[i * cols + j];
}

/**
 * the () operator. gets two indexes
 * ints (i,j) and returns the (i,j) coordination
 * of the current matrix.
 * @param i - row index
 * @param j - column index
 * @return the (i,j) coordination
 */
const float &Matrix::operator()(const int &i, const int &j) const {
    if (i >= rows || j >= cols || i < MINIMAL_ROWS_COLS ||
    j < MINIMAL_ROWS_COLS) {
        throw std::out_of_range(OUT_OF_RANGE_ERROR);
    }
    return mat[i * cols + j];
}

/**
 * the () operator. gets index i (int)
 * returns the [i] coordination
 * of the current matrix.
 * @param i -  index
 * @return the [i] coordination
 */
float &Matrix::operator[](const int &i) {
    if (i >= rows * cols || i < MINIMAL_ROWS_COLS) {
        throw std::out_of_range(OUT_OF_RANGE_ERROR);
    }
    return mat[i];
}

/**
 * the () operator. gets index i (int)
 * returns the [i] coordination
 * of the current matrix.
 * @param i -  index
 * @return the [i] coordination
 */
const float& Matrix::operator[](const int & i) const
{
    if (i >= rows * cols || i < MINIMAL_ROWS_COLS) {
        throw std::out_of_range(OUT_OF_RANGE_ERROR);
    }
    return mat[i];
}

/**
 * the output operator. prints the matrix after the activation.
 * @param os - output stream
 * @param rhs - the "right" matrix
 * @return - the "updated" stream
 */
std::ostream& operator << (std::ostream &os, const Matrix& rhs)
{
    for (int i = 0; i < rhs.rows; ++i) {
        for (int j = 0; j < rhs.cols; ++j) {
            if (rhs(i,j) > THRESHOLD)
            {
                os << "**";
            }
            else
            {
                os << "  ";
            }
        }
        os << std::endl;
    }
    return os;
}


// lab support + https://bit.ly/3pU1PRD
/**
 * the input operator.
 * @param os - input stream
 * @param rhs - the "right" matrix
 * @return - the "updated" stream
 */
std::istream& operator >> (std::istream &in, const Matrix& rhs)
{
    if(in.good())
    {
        in.read((char*)rhs.mat, rhs.rows*rhs.cols*(sizeof (float)));
        return in;
    }
    throw std::runtime_error(RUNTIME_ERROR);
}


