/**
* @brief Various Matrix operations.
* @file matrix.h
* None of the matrix operations below change the input matrices if an input is required. They all return a new matrix with the new changes.
* Because memory issues are so prevelant, be sure to use the @freeMatrix function to reclaim some of that memory.
**/

#ifndef _MATRIX_H_
#define _MATRIX_H_

/**
* A struct representing a matrix
**/
typedef struct _matrix {
    int height;
    int width;
    double* data;
} matrix;

/**
* @brief Asserts a condition is true
*
* If the assertion is non-zero (i.e. true), then it returns.
* If the assertion is zero (i.e. false), then it display the string and
* aborts the program.
* This is ment to act like Python's assert keyword.
**/
void assert(int assertion, const char* message);

/**
 * @brief Makes a matrix with a width and height parameters.
 **/
matrix* makeMatrix(int width, int height);

/**
* @brief Copies a matrix. This function uses scaleMatrix, because scaling matrix
* by 1 is the same as a copy.
*
* @param m a pointer to the matrix
* @return a copied matrix
**/
matrix* copyMatrix(matrix* m);

/**
 * @brief Frees the resources of a matrix
 * @param the matrix to free
 **/
void freeMatrix(matrix* m);

/**
* @brief Prints a matrix.
* @param the matrix
**/
void printMatrix(matrix* m);

//============================
// Basic Matrix operations
//============================
/**
 * @brief Returns an identity matrix of size n by n.
 * @param n the input matrix.
 * parameter.
 **/
matrix* identityMatrix(int n);
double traceMatrix(matrix* m);
matrix* transposeMatrix(matrix* m);
matrix* meanMatrix(matrix* m);
matrix* multiplyMatrix(matrix* a, matrix* b);
matrix* scaleMatrix(matrix* m, double value);
matrix* covarianceMatrix(matrix* m);
void rowSwap(matrix* a, int p, int q); // This method changes the input matrix.
matrix* dotProductMatrix(matrix* a, matrix* b);
matrix* dotDiagonalMatrix(matrix* a, matrix* b);
matrix* L2_distance(matrix* a, matrix* b);

#endif
