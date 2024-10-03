#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H

/**
 * the typedef for the functions that
 * * makes the code more readable
 */
typedef Matrix (*function) (const Matrix&m);

/**
 * the namespace itself. includes relu and softmax(implementation in cpp file).
 */
namespace activation
{
    /**
     * this function makes the matrix non-negative (replace the negative
     * elements with 0, and keeps the positive element).
     * @param m - the matrix we want to "relu".
     * @return the matrix as non-negative matrix.
     */
    Matrix relu(const Matrix&m);

    /**
     * this function replace every element x with e^x, and then divide every
     * element in the sum of all elements
     * @param m - the matrix we want to "softmax"
     * @return the matrix as "softmaxed"
     */
    Matrix softmax(const Matrix&m);

}

#endif //ACTIVATION_H