//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Dense.h"
#include "Activation.h"
#include "Digit.h"

#define MLP_SIZE 4

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784}, {64, 128},
                                  {20, 64}, {10, 20}};
const MatrixDims biasDims[]    = {{128, 1}, {64, 1}, {20, 1},  {10, 1}};

class MlpNetwork
{
private:
    Dense *layers[MLP_SIZE]{};

public:

    /**
     * constructor for Mlp network class.
     * @param weights - array of weights for each layer.
     * @param biases -
     */
    MlpNetwork(Matrix weights[], Matrix biases[]);

    /**
     * Applies the entire network on input,
     * @param mat - image as a 28x28 matrix.
     * @return - digit struct.
     */
    Digit operator()(const Matrix& mat);
};

#endif // MLPNETWORK_H
