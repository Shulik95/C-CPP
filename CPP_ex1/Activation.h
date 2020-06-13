//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    Relu,
    Softmax
};

/**
 * decelerations for Activation class.
 */
class Activation
{

private:
    ActivationType aType;

    /**
     * activate Relu function on each item of the matrix.
     * @param mat - input matrix for function.
     * @return - Matrix object by val.
     */
    Matrix _reluForEach(const Matrix& mat) const;

    /**
     * activate Softmax function on each item of the matrix.
     * @param mat - input matrix for function.
     * @return - Matrix object by val.
     */
    Matrix _softMaxForEach(const Matrix& mat) const;


public:
    /**
     * constructor for Activation class.
     * @param actType - type of activation function.
     */
    Activation(ActivationType actType);

    /**
     * @return - activationType of object.
     */
    ActivationType getActivationType() const;

    /**
     * applies activation function on input, doesnt change input!
     * @param mat - input for function.
     * @return - A new Matrix which represents the
     */
    Matrix operator()(const Matrix& mat) const;
};

#endif //ACTIVATION_H
