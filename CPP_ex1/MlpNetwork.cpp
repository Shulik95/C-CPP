/**
 * @file Dense.cpp
 * @author  Shalom Kachko
 * @date 12 june 2020
 *
 * @brief represents a layer of the network.
 */

// ------------------------------ includes ------------------------------
#include "Matrix.h"
#include "Dense.h"
#include "MlpNetwork.h"

// -------------------------- const definitions -------------------------
#define SEC_LAYER 1
#define THIRD_LAYER 2
#define FINAL_LAYER 3
#define INIT_VAL 0
#define FINAL_SIZE 10

// ------------------------------- methods ------------------------------

/**
 * constructor for Mlp network class.
 * @param weights - array of weights for each layer.
 * @param biases -
 */
MlpNetwork::MlpNetwork(Matrix weights[], Matrix biases[]) : \
layers{Dense(weights[INIT_VAL],biases[INIT_VAL],Relu),
       Dense(weights[SEC_LAYER], biases[SEC_LAYER], Relu),
       Dense(weights[THIRD_LAYER], biases[THIRD_LAYER], Relu),
       Dense(weights[FINAL_LAYER], biases[FINAL_SIZE], Softmax)}
{
}

/**
 * Applies the entire network on input,
 * @param mat - image as a 28x28 matrix.
 * @return - digit struct.
 */
Digit MlpNetwork::operator()(const Matrix &mat)
{
    Digit retDig;
    Matrix r1 = Matrix(mat);
    retDig.probability = INIT_VAL;
    retDig.value = INIT_VAL;
    for (auto layer : this->layers)
    {
        r1 = layer(r1);
    }
    /*r1 is a length 10 vector now*/
    for(int i = 0; i < FINAL_SIZE; i++)
    {
        if(r1[i] > retDig.probability)
        {
            retDig.probability = r1[i];
            retDig.value = i;
        }
    }
    return retDig;
}


