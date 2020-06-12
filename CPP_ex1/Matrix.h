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
#include <iostream>
// -------------------------- const definitions -------------------------
#ifndef MATRIX_H
#define MATRIX_H
#define DEFAULT 1

// ------------------------------- methods ------------------------------


/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
    int rows, cols;
} MatrixDims;

class Matrix
{
private:
    int rows = 0;
    int cols = 0;
    float **mat = nullptr;

    /**
     * checks if given values for matrix rows and column vars are positive.
     */
    void checkValid();

    /**
     * zeroes all given values in matrix.
     */
    void zeroMatrix();

    /**
     * free all memory used by matrix.
     */
    void deAllocMatrix();

    /**
     * inits a two dim array according to rows and cols of the matrix, assumes they are assigned.
     */
    void initMatrix();



public:
    /**
     * Constructs matrix of size row X cols, Inits all elements to 0
     * @param row - number of rows.
     * @param cols - number of columns.
     */
    Matrix(int rows, int cols);

    /**
     * Constructs 1x1 Matrix, single elemnts is inited to 0;
     */
    Matrix() : Matrix(DEFAULT,DEFAULT){};

    /**
     * Constructs a matrix based on given matrix.
     * @param m - copies given matrix.
     */
    Matrix(const Matrix& m);

    /**
     * Destructor for Matrix class objects.
     */
    ~Matrix();

    /**
     * @return returns the amount of rows as int
     */
    int getRows() const {
        return rows;
    }

    /**
     * @return - returns the amount
     */
    int getCols() const {
        return cols;
    }

    /**
     * transforms a matrix into a column vector, supports function calling concatenation.
     */
    Matrix& vectorize();

    /**
     * Prints matrix elements.
     */
    void plainPrint() const;

    /**
     * assigns given matrix to our matrix.
     * @param rhs - matrix to copy.
     * @return - reference to new matrix.
     */
    Matrix& operator=(const Matrix &rhs);

    /**
     * Matrix addition accumulation.
     * @param rhs - the values to add.
     * @return - refrence to matrix after adding given rhs Matrix.
     */
    Matrix& operator+=(const Matrix& rhs);


    /**
     * multiplies the matrix by given scalar c from the right side.
     * @param c - scalar to multiply by
     * @return - returns reference to Matrix object.
     */
    Matrix operator*(float c);

    /**
     * for given row, col returns the row,col element of the matrix.
     * @param row - row number.
     * @param col - columns number.
     */
    float& operator()(int row, int col);

    /**
     * for given row, col returns the row,col element of the matrix.
     * @param row - row number.
     * @param col - columns number.
     */
    const float& operator()(int row, int col) const;

    /**
     * for given index returns the idx'th item in the matrix.
     * @param idx - the number of the item to get.
     */
    float& operator[](int idx);

    /**
     * for given index returns the idx'th item in the matrix.
     * @param idx - the number of the item to get.
     */
    const float& operator[](int idx) const;

    /**
     * sums two matrices.
     * @param rhs - rhs matrix to add.
     * @return - a new matrix where each index is the sum of the two given matrices.
     */
    Matrix operator+(const Matrix& rhs) const;

    /**
     * multiplies the matrix by given scalar from the left side.
     * @param c - scalar to multiply by
     * @return - refrence to given matrix, changed by scalar.
     */
    friend Matrix operator*(float c, Matrix& mat);


    /**
    * multiplies two given matrices.
    * @return - return a new matrix which is a multiplication of given matrices.
    */
    Matrix operator*(Matrix &rhs);

    /**
     * inputs data from given and fills matrix.
     * @param s - given input stream.
     * @param mat - matrix to fill.
     */
    friend std::istream& operator>>(std::istream& s, Matrix& mat);

    /**
     * outputs the matrix into stdout as explained in section 3.4
     * @param s - output stream.
     * @param mat - matrix to print.
     */
    friend std::ostream& operator<<(std::ostream& s, const Matrix& mat);
};

#endif //MATRIX_H
