#include "3DViewer.h"

// Создание матриц (create_matrix)
int create_matrix(int rows, int cols, matrix_t *result) {
  int rez = OK;
  double *ptr = NULL;
  result->rows = rows;
  result->cols = cols;
  result->matrix =
      (double **)malloc(sizeof(double *) * rows + sizeof(double) * cols * rows);
  if (result->matrix == NULL) {
    rez = INCORECT;
  } else {
    ptr = (double *)(result->matrix + rows);
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (ptr + cols * i);
    }
  }
  return rez;
}