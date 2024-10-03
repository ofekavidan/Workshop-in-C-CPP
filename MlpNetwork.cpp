//
// Created by Ofek Avidan on 27/08/2022.
//

#include "MlpNetwork.h"

#define VECTOR_PROBABILITY_SIZE 10

/**
 * the constructor of the MlpNetwork. gets two arrays (first - of weights,
 * second - of biases).
 * @param weights - y = f (W ⋅ x + b). called "weight matrix".
 * @param bias - b ∈ ℝn. vector that called the "bias" of the layer.
 */
MlpNetwork::MlpNetwork(Matrix weights [], Matrix biases[]) :
layers{Dense(weights[0],biases[0], activation::relu),
        Dense(weights[1],biases[1], activation::relu),
        Dense(weights[2],biases[2], activation::relu),
        Dense(weights[3],biases[3], activation::softmax)}
{

}

/**
 * this function "process" the image we got from user
 * @param img - the image itself.
 * @return the matrix after the activation function.
 */
digit MlpNetwork::operator()(const Matrix& img)
{
    Matrix first_result = layers[0](img);
    Matrix second_result =  layers[1](first_result);
    Matrix third_result =  layers[2](second_result);
    Matrix fourth_result =  layers[3](third_result);
//    Matrix result = layers[3](layers[2](layers[1](layers[0](img))));

    float max = 0;
    unsigned int index = 0;
    for (int i = 0; i < VECTOR_PROBABILITY_SIZE; ++i) {
        if(fourth_result(i,0) > max)
        {
            max = fourth_result(i,0);
            index = i;
        }
    }
    digit prob = digit{index,max};
    return prob;
}


