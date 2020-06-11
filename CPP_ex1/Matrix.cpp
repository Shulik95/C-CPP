/**
 * @file Matrix.cpp
 * @author  Shalom Kachko
 * @date 11 june 2020
 *
 * @brief Matrix implementation for neural network
 *
 * @section DESCRIPTION
 *
 */

// ------------------------------ includes ------------------------------
#include "Matrix.h"
#include <string>

// -------------------------- const definitions -------------------------
const std::string NEG_INPUT_MSG= "Error: given input has negative number of rows or columns";
const std::string ALLOC_FAILED = "Error: memory allocation failed :(";
// ------------------------------- methods ------------------------------
/**
 * Constructs matrix of size row X cols, Inits all elements to 0
 * @param row - number of rows.
 * @param cols - number of columns.
 */
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols)
{
    this->checkValid();
    this->mat = new(std::nothrow) float* [rows];
    if(this->mat == nullptr)
    {
        std::cerr << ALLOC_FAILED << std::endl;
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < rows; i++)
    {
        this->mat[i] = new(std::nothrow) float[cols];
        std::cerr << ALLOC_FAILED << std::endl;
        exit(EXIT_FAILURE);
    }
    this->zeroMatrix();
}

/**
 * checks if given values for matrix rows and column vars are positive.
 */
void Matrix::checkValid()
{
    if(this->rows <=0 || this->cols <= 0)
    {
        std::cerr << NEG_INPUT_MSG << std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * zeroes all given values in matrix.
 */
void Matrix::zeroMatrix()
{
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->cols; j++)
        {
            this->mat[i][j] = DEFAULT;
        }
    }
}
