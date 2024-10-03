#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

/**
 * the class itself. responsible for using the activation functions from
 * namespace::activation
 */
class Dense {
private:
    Matrix weights;
    Matrix bias;
    function ActivationFunction;

public:
    /**
     * the constructor of the class
     * @param weights - y = f (W ⋅ x + b). called "weight matrix".
     * @param bias - b ∈ ℝn. vector that called the "bias" of the layer.
     * @param ActivationFunction f : ℝn → ℝn. the activation function of the
     * layers. (always be a relu, except the last layer (softmax)).
     */
    Dense(const Matrix& weights,const Matrix& bias,
          function ActivationFunction);
    /**
     * this function return the weights.
     * @return weights - y = f (W ⋅ x + b). called "weight matrix".
     */
    Matrix get_weights() const;
    /**
     * this function return the bias.
     * @return bias - b ∈ ℝn. vector that called the "bias" of the layer.
     */
    Matrix get_bias() const;
    /**
     * this function return the activation function
     * @return ActivationFunction f : ℝn → ℝn. the activation function of the
     * layers. (always be a relu, except the last layer (softmax)).
     */
    function get_activation() const;
    /**
     *
     * @param input - the input matrix of every layer
     * @return the appropriate matrix. (uses activation function on the input
     * matrix).
     */
    Matrix operator()(const Matrix& input);
};

#endif //DENSE_H
