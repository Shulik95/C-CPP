

#ifndef CPP_EX1_DENSE_H
#define CPP_EX1_DENSE_H

#include "Matrix.h"
#include "Activation.h"

/**
 * 
 */
class Dense
{
private:
    Matrix weights;
    Matrix bias;
    Activation activation;

public:

    /**
     * Constructor for Dense class.
     * @param w - Matrix object holding weights.
     * @param bias - Matrix.
     */
    Dense(Matrix& w, Matrix& bias, ActivationType);

    /**
     * @return - Returns the weights of this layer as a Matrix obj.
     */
    const Matrix &getWeights() const;

    /**
     * @return - Returns the bias of this layer as a Matrix.
     */
    const Matrix &getBias() const;

    /**
     * @return - the Activation obj of the layer.
     */
    const Activation &getActivation() const;

    /**
     * Applies the layer on inputed Matrix.
     * @param mat - input to
     * @return
     */
    Matrix operator()(const Matrix& mat);
};

#endif //CPP_EX1_DENSE_H
