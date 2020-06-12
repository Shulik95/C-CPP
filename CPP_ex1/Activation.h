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

class Activation
{

private:
    ActivationType aType;

public:
    /**
     * constructor for Activation class.
     * @param actType - type of activation function.
     */
    Activation(ActivationType actType);

    /**
     * @return - activationType of object.
     */
    ActivationType getActivation() const;

    /**
     * applies activation function on input, doesnt change input!
     * @param mat - input for function.
     * @return - A new Matrix which represents the
     */
    Matrix operator()(Matrix& mat);

    ActivationType getAType() const;

};

#endif //ACTIVATION_H
