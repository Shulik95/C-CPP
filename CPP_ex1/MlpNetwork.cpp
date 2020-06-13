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
MlpNetwork::MlpNetwork(Matrix weights[], Matrix biases[]) : layer1(Dense(weights[0], biases[0], Relu)),
layer2(Dense(weights[1], biases[1], Relu)),
layer3(Dense(weights[2], biases[2], Relu)),
layer4(Dense(weights[3], biases[3], Softmax))
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
    r1 = layer1(r1);
    r1 = layer2(r1);
    r1 = layer3(r1);
    r1 = layer4(r1);

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


