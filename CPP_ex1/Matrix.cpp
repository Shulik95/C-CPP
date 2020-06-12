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
const std::string IDX_OUT_OF_RANGE = "Error: this index is out of matrix range";

const int DEF_VAL = 0;
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
        if(this->mat[i] == nullptr)
        {
            std::cerr << ALLOC_FAILED << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    this->zeroMatrix();
}

/**
     * Constructs a matrix based on given matrix.
     * @param m - copies given matrix.
     */
Matrix::Matrix(const Matrix& m) : Matrix(m.getRows(), m.getCols())
{
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
            this->mat[i][j] = DEF_VAL;
        }
    }
}

/**
 * Prints matrix elements.
 */
void Matrix::plainPrint() const
{
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->cols; j++)
        {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << "" << std::endl;
    }
}

/**
     * for given row, col returns the row,col element of the matrix.
     * @param row - row number.
     * @param col - columns number.
     */
float & Matrix::operator()(const int row, const int col) const
{
    return this->mat[row][col];
}

/**
 * destructor for Matrix class, free memory allocated for matrix.
 */
Matrix::~Matrix()
{
    this->deAllocMatrix();
}

/**
 * transofrms given matrix into a column vector.
 * @return - a Matrix object of size (row X cols)X1/
 */
Matrix& Matrix::vectorize()
{
    float** vector = new(std::nothrow) float*[this->rows * this->cols];
    if(vector == nullptr)
    {
        std::cerr << ALLOC_FAILED << std::endl;
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < (this->rows * this->cols); i++)
    {
        vector[i] = new float[DEFAULT]; //alloc array of size 1
        if(vector[i] == nullptr)
        {
            std::cerr << ALLOC_FAILED << std::endl;
            exit(EXIT_FAILURE);
        }
        vector[i][DEF_VAL] = (*this)[i]; //get corresponding value from original matrix.
    }
    this->deAllocMatrix();
    this->rows = this->rows * this->cols;
    this->cols = DEFAULT;
    this->mat = vector;
    return *this;
}

/**
 * frees all memory which was dynamically allocated by matrix.
 */
void Matrix::deAllocMatrix()
{
    if(this->mat != nullptr && *(this->mat) != nullptr)
    {
        for(int i = 0; i < this->rows; i++)
        {
            delete[] this->mat[i];
        }
        delete[] this->mat;
        this->mat = nullptr;
    }
}

/**
 * for given index returns the idx'th item in the matrix.
 * @param idx - the number of the item to get.
 */
float& Matrix:: operator[](const int idx) const
{
    if(idx >= this->getRows() * this->getCols() || idx < 0) //index out of range
    {
        std::cerr << IDX_OUT_OF_RANGE << std::endl;
        exit(EXIT_FAILURE);
    }
    return this->mat[(idx/this->getRows())][idx % this->getCols()];
}

int main()
{
    Matrix m = Matrix(10, 10);
    for(int i = 0; i < 100; i++)
    {
        m[i] = (float)i;
    }
    m.plainPrint();
    m.vectorize();
    m.plainPrint();
}
