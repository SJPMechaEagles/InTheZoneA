/**
 * @brief Various Matrix operations.
 * @file matrix.h
 * None of the matrix operations below change the input matrices if an input is
 * required. They all return a new matrix with the new changes. Because memory
 * issues are so prevelant, be sure to use the @freeMatrix function to reclaim
 * some of that memory.
 **/

#ifndef _MATRIX_H_
#define _MATRIX_H_

/**
 * A struct representing a matrix
 **/
typedef struct _matrix {
  int height;
  int width;
  double *data;
} matrix;

/**
 * @brief Asserts a condition is true
 *
 * If the assertion is non-zero (i.e. true), then it returns.
 * If the assertion is zero (i.e. false), then it display the string and
 * aborts the program.
 * This is ment to act like Python's assert keyword.
 * @param assertion the condition, acts like a bollean 0 = false else true
 * @param message the message to print if it fails
 **/
void assert(int assertion, const char *message);

/**
 * @brief Makes a matrix with a width and height parameters.
 *  @param width The width of the matrix
 * @param height the height of the matrix
 * @return the new matrix
 **/
matrix *makeMatrix(int width, int height);

/**
 * @brief Copies a matrix. This function uses scaleMatrix, because scaling
 *matrix by 1 is the same as a copy.
 *
 * @param m a pointer to the matrix
 * @return a copied matrix
 **/
matrix *copyMatrix(matrix *m);

/**
 * @brief Frees the resources of a matrix
 * @param m the matrix to free
 **/
void freeMatrix(matrix *m);

/**
 * @brief Prints a matrix.
 * @param m the matrix
 **/
void printMatrix(matrix *m);

/**
 * @brief Returns an identity matrix of size n by n.
 * @param n the input matrix.
 * parameter.
 **/
matrix *identityMatrix(int n);

/**
 * @brief Given an "m rows by n columns" matrix
 * @return the sum of the elements
 * along the diagonal.
 * param m the matrix to trace
 **/
double traceMatrix(matrix *m);

/**
 * @brief returns the transpose matrix.
 * @param the matrix to transpose.
 * @return the transposed matrix.
 **/
matrix *transposeMatrix(matrix *m);

/**
 * @brief Given an "m rows by n columns" matrix, return a matrix where each
 * element represents the mean of that full column.
 * @param m the matrix
 * @return matrix with 1 row and n columns each element represents the mean of
 * that full column.
 **/
matrix *meanMatrix(matrix *m);

/**
 * @brief Given a two matrices, returns the multiplication of the two.
 * @param a the first matrix
 * @param b the seconf matrix
 * return the result of the multiplication
 **/
matrix *multiplyMatrix(matrix *a, matrix *b);

/**
 * @brief scales a matrix.
 * @param m the matrix to scale
 * @param value the value to scale by
 * @return a new matrix where each element in the input matrix is
 * multiplied by the scalar value
 **/
matrix *scaleMatrix(matrix *m, double value);

/**
 * @brief returns the covariance of the matrix
 * @param m the matrix
 * @return a matrix with n row and n columns, where each element represents
 *covariance of 2 columns.
 **/
matrix *covarianceMatrix(matrix *m);

/**
 * @brief swaps the rows of a matrix. This method changes the input matrix.
 * Given a matrix, this algorithm will swap rows p and q, provided
 * that p and q are less than or equal to the height of matrix A and p
 * and q are different values.
 * @param a the matrix to swap. This method changes the input matrix.
 * @param p the first row
 * @param q the second row
 **/
void rowSwap(matrix *a, int p, int q);
/**
 * @brief returns the matrix dot product.
 * Given a two matrices (or the same matrix twice) with identical widths and
 * different heights, this method returns a a->height by b->height matrix of
 * the cross product of each matrix.
 *
 * Dot product is essentially the sum-of-squares of two vectors.
 *
 * Also, if the second paramter is NULL, it is assumed that we
 * are performing a cross product with itself.
 * @param a the first matrix
 * @param b the second matrix
 * @return the result of the dot product
 **/
matrix *dotProductMatrix(matrix *a, matrix *b);

/**
 * @brief performs a diagonial matrix dot product.
 * Given a two matrices (or the same matrix twice) with identical widths and
 * heights, this method returns a 1 by a->height matrix of the cross
 * product of each matrix along the diagonal.
 *
 * Dot product is essentially the sum-of-squares of two vectors.
 *
 * If the second paramter is NULL, it is assumed that we
 * are performing a cross product with itself.
 * @param a the first matrix
 * @param b the second matrix
 * @return the matrix result
 **/
matrix *dotDiagonalMatrix(matrix *a, matrix *b);

#endif
