//
// Created by Ofek Avidan on 27/08/2022.
//
#include <cmath>
//#include <math.h>
#include "Activation.h"

// See full documentation in header file
namespace activation
{
    // See full documentation in header file
    Matrix relu(const Matrix &m) {
        Matrix new_matrix = Matrix(m.get_rows(), m.get_cols());

        for (int i = 0; i < m.get_rows(); ++i) {
            for (int j = 0; j <  m.get_cols(); ++j) {
                if (m(i,j) < 0)
                {
                    new_matrix(i, j) = 0;
                }
                else
                {
                    new_matrix(i, j) = m(i,j);
                }
            }
        }
        return new_matrix;
    }

    // See full documentation in header file
    Matrix softmax(const Matrix &m) {
        Matrix new_matrix = Matrix(m.get_rows(), m.get_cols());

        for (int i = 0; i < m.get_rows(); ++i) {
            for (int j = 0; j < m.get_cols(); ++j) {
                new_matrix(i, j) = std::exp(m(i,j));
            }
        }
        float sum = 0;
        for (int i = 0; i < m.get_rows() * m.get_cols(); ++i) {
            sum+=new_matrix[i];
        }
        new_matrix = (1/sum) * new_matrix;
        return new_matrix;
    }
}