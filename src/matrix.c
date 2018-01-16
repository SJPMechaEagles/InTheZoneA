#include "matrix.h"
#include "log.h"
#include <API.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Asserts a condition is true
 *
 * If the assertion is non-zero (i.e. true), then it returns.
 * If the assertion is zero (i.e. false), then it display the string and
 * aborts the program.
 * This is ment to act like Python's assert keyword.
 **/
void assert(int assertion, const char *message) {
  if (assertion == 0) {
    error(message);
    exit(1);
  }
}

/**
 * @brief Makes a matrix with a width and height parameters.
 * @param width The width of the matrix
 * @param height the height of the matrix
 * @return the new matrix
 **/
matrix *makeMatrix(int width, int height) {
  matrix *out;
  assert(width > 0 && height > 0, "New matrix must be at least a 1 by 1");
  out = (matrix *)malloc(sizeof(matrix));

  assert(out != NULL, "Out of memory.");

  out->width = width;
  out->height = height;
  out->data = (double *)malloc(sizeof(double) * width * height);

  assert(out->data != NULL, "Out of memory.");

  memset(out->data, 0.0, width * height * sizeof(double));

  return out;
}

/**
 * @brief Copies a matrix. This function uses scaleMatrix, because scaling
 *matrix by 1 is the same as a copy.
 *
 * @param m a pointer to the matrix
 * @return a copied matrix
 **/
matrix *copyMatrix(matrix *m) { return scaleMatrix(m, 1); }

/**
 * @brief Frees the resources of a matrix
 * @param the matrix to free
 **/
void freeMatrix(matrix *m) {
  if (m != NULL) {
    if (m->data != NULL) {
      free(m->data);
      m->data = NULL;
    }
    free(m);
  }
  return;
}

/**
 * @brief Prints a matrix.
 * @param the matrix
 **/
void printMatrix(matrix *m) {
  int i, j;
  double *ptr = m->data;
  printf("%d %d\n", m->width, m->height);
  for (i = 0; i < m->height; i++) {
    for (j = 0; j < m->width; j++) {
      printf(" %9.6f", *(ptr++));
    }
    printf("\n");
  }
  return;
}

/**
 * @brief Returns an identity matrix of size n by n.
 * @param n the input matrix.
 * @return the identity matrix
 * parameter.
 **/
matrix *identityMatrix(int n) {
  int i;
  matrix *out;
  double *ptr;

  assert(n > 0, "Identity matrix must have value greater than zero.");

  out = makeMatrix(n, n);
  ptr = out->data;
  for (i = 0; i < n; i++) {
    *ptr = 1.0;
    ptr += n + 1;
  }

  return out;
}

/**
 * @brief Given an "m rows by n columns" matrix returns the sum
 * @return the sum of the elements
 * along the diagonal.
 **/
double traceMatrix(matrix *m) {
  int i;
  int size;
  double *ptr = m->data;
  double sum = 0.0;

  if (m->height < m->width) {
    size = m->height;
  } else {
    size = m->width;
  }

  for (i = 0; i < size; i++) {
    sum += *ptr;
    ptr += m->width + 1;
  }

  return sum;
}

/**
 * @brief Given an "m rows by n columns" matrix, return a matrix where each
 *element represents the mean of that full column.
 * @pram the matrix
 * @return matrix with 1 row and n columns each element represents the mean of
 *that full column.
 **/
matrix *meanMatrix(matrix *m) {
  int i, j;
  matrix *out;

  assert(m->height > 0, "Height of matrix cannot be zero.");

  out = makeMatrix(m->width, 1);

  for (i = 0; i < m->width; i++) {
    double *ptr;
    out->data[i] = 0.0;
    ptr = &m->data[i];
    for (j = 0; j < m->height; j++) {
      out->data[i] += *ptr;
      ptr += out->width;
    }
    out->data[i] /= (double)m->height;
  }
  return out;
}

/**
 * @brief returns the covariance of the matrix
 * @param the matrix
 * @return a matrix with n row and n columns, where each element represents
 *covariance of 2 columns.
 **/
matrix *covarianceMatrix(matrix *m) {
  int i, j, k = 0;
  matrix *out;
  matrix *mean;
  double *ptrA;
  double *ptrB;
  double *ptrOut;

  assert(m->height > 1, "Height of matrix cannot be zero or one.");

  mean = meanMatrix(m);
  out = makeMatrix(m->width, m->width);
  ptrOut = out->data;

  for (i = 0; i < m->width; i++) {
    for (j = 0; j < m->width; j++) {
      ptrA = &m->data[i];
      ptrB = &m->data[j];
      *ptrOut = 0.0;
      for (k = 0; k < m->height; k++) {
        *ptrOut += (*ptrA - mean->data[i]) * (*ptrB - mean->data[j]);
        ptrA += m->width;
        ptrB += m->width;
      }
      *ptrOut /= m->height - 1;
      ptrOut++;
    }
  }

  freeMatrix(mean);
  return out;
}

/**
 * @brief returns the transpose matrix.
 * @param the matrix to transpose.
 * @return the transposed matrix.
 **/
matrix *transposeMatrix(matrix *m) {
  matrix *out = makeMatrix(m->height, m->width);
  double *ptrM = m->data;
  int i, j;

  for (i = 0; i < m->height; i++) {
    double *ptrOut;
    ptrOut = &out->data[i];
    for (j = 0; j < m->width; j++) {
      *ptrOut = *ptrM;
      ptrM++;
      ptrOut += out->width;
    }
  }

  return out;
}

/**
 * @brief Given a two matrices, returns the multiplication of the two.
 * @param a the first matrix
 * @param b the seconf matrix
 * return the result of the multiplication
 **/
matrix *multiplyMatrix(matrix *a, matrix *b) {
  int i, j, k;
  matrix *out;
  double *ptrOut;
  double *ptrA;
  double *ptrB;

  assert(a->width == b->height,
         "Matrices have incorrect dimensions. a->width != b->height");

  out = makeMatrix(b->width, a->height);
  ptrOut = out->data;

  for (i = 0; i < a->height; i++) {

    for (j = 0; j < b->width; j++) {
      ptrA = &a->data[i * a->width];
      ptrB = &b->data[j];

      *ptrOut = 0;
      for (k = 0; k < a->width; k++) {
        *ptrOut += *ptrA * *ptrB;
        ptrA++;
        ptrB += b->width;
      }
      ptrOut++;
    }
  }

  return out;
}

/**
 * @brief scales a matrix.
 * @param m the matrix to scale
 * @param the value to scale by
 * @return a new matrix where each element in the input matrix is
 * multiplied by the scalar value
 **/
matrix *scaleMatrix(matrix *m, double value) {
  int i, elements = m->width * m->height;
  matrix *out = makeMatrix(m->width, m->height);
  double *ptrM = m->data;
  double *ptrOut = out->data;

  for (i = 0; i < elements; i++) {
    *(ptrOut++) = *(ptrM++) * value;
  }

  return out;
}

/**
 * @brief swaps the rows of a matrix. This method changes the input matrix.
 * Given a matrix, this algorithm will swap rows p and q, provided
 * that p and q are less than or equal to the height of matrix A and p
 * and q are different values.
 * @param the matrix to swap. This method changes the input matrix.
 * @param the first row
 * @param the second row
 **/
void rowSwap(matrix *a, int p, int q) {
  int i;
  double temp;
  double *pRow;
  double *qRow;

  assert(a->height > 2, "Matrix must have at least two rows to swap.");
  assert(p < a->height && q < a->height,
         "Values p and q must be less than the height of the matrix.");

  // If p and q are equal, do nothing.
  if (p == q) {
    return;
  }

  pRow = a->data + (p * a->width);
  qRow = a->data + (q * a->width);

  // Swap!
  for (i = 0; i < a->width; i++) {
    temp = *pRow;
    *pRow = *qRow;
    *qRow = temp;
    pRow++;
    qRow++;
  }

  return;
}

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
 * @param the second matrix
 * @return the result of the dot product
 **/
matrix *dotProductMatrix(matrix *a, matrix *b) {
  matrix *out;
  double *ptrOut;
  double *ptrA;
  double *ptrB;
  int i, j, k;

  if (b != NULL) {
    assert(a->width == b->width,
           "Matrices must be of the same dimensionality.");
  }

  // Are we computing the sum of squares of the same matrix?
  if (a == b || b == NULL) {
    b = a; // May not appear safe, but we can do this without risk of losing b.
  }

  out = makeMatrix(b->height, a->height);
  ptrOut = out->data;

  for (i = 0; i < a->height; i++) {
    ptrB = b->data;

    for (j = 0; j < b->height; j++) {
      ptrA = &a->data[i * a->width];

      *ptrOut = 0;
      for (k = 0; k < a->width; k++) {
        *ptrOut += *ptrA * *ptrB;
        ptrA++;
        ptrB++;
      }
      ptrOut++;
    }
  }

  return out;
}

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
matrix *dotDiagonalMatrix(matrix *a, matrix *b) {
  matrix *out;
  double *ptrOut;
  double *ptrA;
  double *ptrB;
  int i, j;

  if (b != NULL) {
    assert(a->width == b->width && a->height == b->height,
           "Matrices must be of the same dimensionality.");
  }

  // Are we computing the sum of squares of the same matrix?
  if (a == b || b == NULL) {
    b = a; // May not appear safe, but we can do this without risk of losing b.
  }

  out = makeMatrix(1, a->height);
  ptrOut = out->data;
  ptrA = a->data;
  ptrB = b->data;

  for (i = 0; i < a->height; i++) {
    *ptrOut = 0;
    for (j = 0; j < a->width; j++) {
      *ptrOut += *ptrA * *ptrB;
      ptrA++;
      ptrB++;
    }
    ptrOut++;
  }

  return out;
}
