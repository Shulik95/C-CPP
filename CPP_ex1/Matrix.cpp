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
#include <fstream>

// -------------------------- const definitions -------------------------
/**
 * general forEach method, applies given op on given matrices.
 */
#define FOR_EACH_OP(op)\
for(int i = 0; i < this->rows; i++)\
{\
for(int j = 0; j < this->cols; j++)\
{\
this->mat[i][j] op rhs.mat[i][j];\
}\
}

/*ops used by function above*/
#define ASSIGN =
#define ADD_ACCU +=

const std::string NEG_INPUT_MSG= "Error: given input has negative number of rows or columns";
const std::string ALLOC_FAILED = "Error: memory allocation failed :(";
const std::string IDX_OUT_OF_RANGE = "Error: this index is out of matrix range";
const std::string ILLEGAL_BINARY_OP = "Error: the dims of the matrices dont match";
const std::string FILE_ERR = "Error: file reading has failed.";
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
    this->initMatrix();
    this->zeroMatrix();
}

/**
     * Constructs a matrix based on given matrix.
     * @param m - copies given matrix.
     */
Matrix::Matrix(const Matrix& m) : Matrix(m.getRows(), m.getCols())
{
    *this = m;
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
        std::cout << std::endl;
    }
}

/**
     * for given row, col returns the row,col element of the matrix.
     * @param row - row number.
     * @param col - columns number.
     */
float & Matrix::operator()(const int row, const int col)
{
    return this->mat[row][col];
}

/**
     * const version of the above function.
     * @param row - row number.
     * @param col - columns number.
     */
const float& Matrix::operator()(int row, int col) const
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
float& Matrix:: operator[](const int idx)
{
    if(idx >= this->getRows() * this->getCols() || idx < 0) //index out of range
    {
        std::cerr << IDX_OUT_OF_RANGE << std::endl;
        exit(EXIT_FAILURE);
    }
    return this->mat[idx / this->getCols()][idx % this->getCols()];
}

/**
 * for given index returns the idx'th item in the matrix.
 * @param idx - the number of the item to get.
 */
const float& Matrix::operator[](int idx) const
{
    return (*this)[idx];
}

/**
 * Matrix addition accumulation.
 * @param rhs - the values to add.
 * @return - refrence to matrix after adding given rhs Matrix.
 */
Matrix &Matrix::operator+=(const Matrix &rhs)
{
    if(this->getCols() != rhs.getCols() || this->getRows() != rhs.getRows())
    {
        std::cerr << ILLEGAL_BINARY_OP << std::endl;
        exit(EXIT_FAILURE);
    }
    FOR_EACH_OP(ADD_ACCU)
    return *this;
}

/**
     * assigns given matrix to our matrix.
     * @param rhs - matrix to copy.
     * @return - reference to new matrix.
     */
Matrix &Matrix::operator=(const Matrix &rhs)
{
    if(this == &rhs)
    {
        return *this;
    }
    this->deAllocMatrix();
    this->rows = rhs.getRows();
    this->cols = rhs.getCols();
    this->initMatrix();
    FOR_EACH_OP(ASSIGN)
    return *this;
}

/**
 * inits a two dim array according to rows and cols of the matrix, assumes they are assigned.
 */
void Matrix::initMatrix()
{
    this->mat = new(std::nothrow) float* [this->rows];
    if(this->mat == nullptr)
    {
        std::cerr << ALLOC_FAILED << std::endl;
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < this->rows; i++)
    {
        this->mat[i] = new(std::nothrow) float[this->cols];
        if(this->mat[i] == nullptr)
        {
            std::cerr << ALLOC_FAILED << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * sums two matrices.
 * @param rhs - rhs matrix to add.
 * @return - a new matrix where each index is the sum of the two given matrices.
 */
Matrix Matrix::operator+(const Matrix &rhs) const
{
    if(this->rows != rhs.getRows() || this->cols != rhs.getCols())
    {
        std::cerr << ILLEGAL_BINARY_OP << std::endl;
        exit(EXIT_FAILURE);
    }
    Matrix ret = Matrix(this->rows, this->cols);
    ret += *this;
    ret += rhs;
    return ret;
}

/**
 * multiplies the matrix by given scalar c from the right side.
 * @param c - scalar to multiply by.
 * @return - returns a Matrix object by val;
 */
Matrix Matrix::operator*(const float c)
{
    Matrix ret = Matrix(*this);
    for (int i = 0; i < (*this).getRows(); ++i)
    {
        for (int j = 0; j < this->getCols(); ++j)
        {
             ret(i, j) *= c;
        }
    }
    return ret;
}

/**
 * multiplies the matrix by given scalar c from the left side.
 * @param c - scalar to multiply by.
 * @param mat - matrix to multiply.
 * @return - returns a new Matrix object by val;
 */
Matrix operator*(const float c, Matrix &mat)
{
    Matrix ret = Matrix(mat);
    for (int i = 0; i < mat.getRows(); ++i)
    {
        for (int j = 0; j < mat.getCols(); ++j)
        {
            ret(i, j) *= c;
        }
    }
    return ret;
}

/**
 * multiplies two given matrices.
 * @param rhs - one of the matrices to mult by.
 * @return - a Matrix object by value which is a outcome the the multiplication.
 */
Matrix Matrix::operator*(Matrix &rhs)
{
    if(this->cols != rhs.getRows())
    {
        std::cerr << ILLEGAL_BINARY_OP << std::endl;
        exit(EXIT_FAILURE);
    }
    Matrix ret = Matrix(this->getRows(), rhs.getCols()); //matrix to return.
    for (int i = 0; i < ret.getRows(); ++i)
    {
        for (int j = 0; j < ret.getCols(); ++j)
        {
            for (int k = 0; k < this->cols; ++k)
            {
                ret(i, j) += ((*this)(i, k) * rhs(k, j));
            }
        }
    }
    return ret;
}
/**
 * inputs data from given and fills matrix.
 * @param s - given input stream.
 * @param mat - matrix to fill.
 */
std::istream &operator>>(std::istream &s, Matrix &mat)
{
    if(mat.mat == nullptr) //matrix was not created
    {
        mat.initMatrix();
        mat.zeroMatrix();
    }
    for (int i = 0; i < mat.getRows(); ++i)
    {
        for (int j = 0; j < mat.getCols(); ++j)
        {
            if(!s.good())
            {
                std::cerr << FILE_ERR << std::endl;
                exit(EXIT_FAILURE);
            }
            s.read(reinterpret_cast<char*>(&(mat.mat[i][j])), sizeof(float));
        }
    }
    return s;
}

/**
* outputs the matrix into stdout as explained in section 3.4
* @param s - output stream.
* @param mat - matrix to print.
*/
std::ostream &operator<<(std::ostream &s, const Matrix &mat)
{
    for (int i = 0; i < mat.rows; ++i)
    {
        for (int j = 0; j < mat.cols ; ++j)
        {
            if(mat(i, j) <= 0.1f)
            {
                std::cout << "  ";
            }
            else
            {
                std::cout << "**";
            }
        }
        std::cout << std::endl;
    }
    std::cout<< std::endl;
    return s;
}


//int main()
//{
//    Matrix m = Matrix(3, 5);
//    Matrix m1 = Matrix(5, 4);
//    Matrix m2;
//    for (int i = 0; i < 15 ; ++i)
//    {
//        m[i] = (float)i+1;
//    }
//    //m.plainPrint();
//
//    for (int i = 0; i < 20 ; ++i)
//    {
//        m1[i] = (float)i+1;
//    }
//    //m1.plainPrint();
////    m2 = m * m1;
////    m2.plainPrint();
//    std::cout << sizeof(float);
//    std::ifstream is;
//
//}
