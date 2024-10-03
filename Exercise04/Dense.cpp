//
// Created by Ofek Avidan on 27/08/2022.
//

#include "Dense.h"

// See full documentation in header file
Dense::Dense(const Matrix& weights, const Matrix& bias,
             function ActivationFunction)
: weights(weights), bias(bias), ActivationFunction(ActivationFunction){
}

// See full documentation in header file
Matrix Dense::get_weights() const
{
    return weights;
}

// See full documentation in header file
Matrix Dense::get_bias() const
{
    return bias;
}

// See full documentation in header file
function Dense::get_activation() const
{
    return ActivationFunction;
}

// See full documentation in header file
Matrix Dense::operator()(const Matrix& input)
{
    return ActivationFunction(weights * input + bias);
}