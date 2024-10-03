//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

// Insert MlpNetwork class here...

class MlpNetwork {
private:
    Dense layers[MLP_SIZE];

public:
    /**
 * the constructor of the MlpNetwork. gets two arrays (first - of weights,
 * second - of biases).
 * @param weights - y = f (W ⋅ x + b). called "weight matrix".
 * @param bias - b ∈ ℝn. vector that called the "bias" of the layer.
 */
    MlpNetwork(Matrix weights [], Matrix biases[]);

    /**
 * this function "process" the image we got from user
 * @param img - the image itself.
 * @return the matrix after the activation function.
 */
    digit operator()(const Matrix& img);
};


#endif // MLPNETWORK_H