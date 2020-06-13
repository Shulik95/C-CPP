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
// -------------------------- const definitions -------------------------
// ------------------------------- methods ------------------------------

/**
 * Constructor for Dense class.
 * @param w - Matrix object holding weights.
 * @param bias - Matrix.
 */
Dense::Dense(Matrix& w, Matrix& bias, ActivationType actType) : weights(w), bias(bias),
                                                                activation(Activation(actType))
{
}

/**
 * @return - Returns the weights of this layer as a Matrix obj.
 */
const Matrix &Dense::getWeights() const
{
    return weights;
}
/**
 * @return - Returns the bias of this layer as a Matrix.
 */
const Matrix &Dense::getBias() const
{
    return bias;
}

/**
 * @return - the Activation obj of the layer.
 */
const Activation &Dense::getActivation() const
{
    return activation;
}

/**
 * Applies the layer on inputed Matrix.
 * @param mat - input to
 * @return
 */
Matrix Dense::operator()(const Matrix &mat)
{

    Matrix ret = Matrix(mat);
    ret = (this->weights * ret) + this->bias; // W1*x +b1
    ret = this->activation(ret); // Relu/Softmax(W1*x +b1)
    return ret;
}