/**
 * @file Activation.cpp
 * @author  Shalom Kachko
 * @date 12 june 2020
 * @brief - describes activation function for neural network.
 */

// ------------------------------ includes ------------------------------
#include "Activation.h"
#include <cmath>
// -------------------------- const definitions -------------------------
// ------------------------------- methods ------------------------------


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

/**
* applies activation function on input, doesnt change input!
* @param mat - input for function.
* @return - A new Matrix which represents the
*/
Matrix Activation::operator()(const Matrix &mat) const
{

    if(this->getActivation() == Relu)
    {
        return this->reluForEach(mat);
    }
    else if( this->getActivation() == Softmax)
    {
        return  this->softMaxForEach(mat);
    }
    return mat;
}

/**
* activate Relu function on each item of the matrix.
* @param mat - input matrix for function.
* @return - Matrix object by val.
*/
Matrix Activation::reluForEach(const Matrix &mat) const
{
    Matrix ret = Matrix(mat);
    for (int i = 0; i < mat.getRows(); ++i)
    {
        for (int j = 0; j < mat.getCols(); ++j)
        {
            if(ret(i, j) >= 0)
            {
                continue;
            }
            else
            {
                ret(i, j) = 0;
            }
        }
    }
    return ret;
}

/**
* activate Softmax function on each item of the matrix.
* @param mat - input matrix for function.
* @return - Matrix object by val.
*/
Matrix Activation::softMaxForEach(const Matrix &mat) const
{
    Matrix ret = Matrix(mat);
    float sigma = 0;
    for (int i = 0; i < ret.getRows(); ++i)
    {
        for (int j = 0; j < ret.getCols(); ++j)
        {
            ret(i, j) = std::exp(ret(i, j));
            sigma += ret(i, j);
        }
    }
    for (int k = 0; k < ret.getRows(); ++k)
    {
        for (int i = 0; i < ret.getCols(); ++i)
        {
            ret(k, i) = (1 / sigma) * ret(k, i);
        }
    }
    return ret;
}


//int main()
//{
//    auto act = Activation(Relu);
//    Matrix m = Matrix(10, 10);
//    Matrix& ref = m;
//    Matrix m2;
//    for(int i = 0; i < 50; i++)
//    {
//        m[i] = (float)i;
//    }
//    for (int j = 50; j < 100; ++j)
//    {
//        m[j] = (float)-j;
//    }
//    m.plainPrint();
//    std::cout << std::endl;
//    m2 = act(m);
//    m2.plainPrint();
//    std::cout << std::endl;
//    auto act2 = Activation(Softmax);
//    m2 = act2(m);
//    m2.plainPrint();
//    float sum = 0;
//    for (int k = 0; k < m2.getRows(); ++k) {
//        for (int i = 0; i < m2.getCols(); ++i) {
//            sum += m2(k,i);
//        }
//    }
//    std::cout << "This sum is: " << sum << std::endl;
//}




