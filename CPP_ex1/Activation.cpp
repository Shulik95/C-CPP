/**
 * @file Activation.cpp
 * @author  Shalom Kachko
 * @date 12 june 2020
 * @brief - describes activation function for neural network.
 */

// ------------------------------ includes ------------------------------
// -------------------------- const definitions -------------------------
// ------------------------------- methods ------------------------------

#include "Activation.h"
#include <cmath>
/**
* constructor for Activation class.
* @param actType - type of activation function.
*/
Activation::Activation(ActivationType actType) : aType(actType){}

/**
* @return - activationType of object.
*/
ActivationType Activation::getActivation() const
{
    return aType;
}

