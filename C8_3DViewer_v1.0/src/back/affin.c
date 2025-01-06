#include "3DViewer.h"

void move_x(matrix_t *A, double a) {
  for (int i = 1; i < A->rows; i++) A->matrix[i][0] += a;
}

void move_y(matrix_t *A, double a) {
  for (int i = 1; i < A->rows; i++) A->matrix[i][1] += a;
}

void move_z(matrix_t *A, double a) {
  for (int i = 1; i < A->rows; i++) A->matrix[i][2] += a;
}

void rotation_by_ox(matrix_t *A, double angle) {
  angle = angle * M_PI / 180;
  for (int i = 1; i < A->rows; i++) {
    double temp_y = A->matrix[i][1];
    double temp_z = A->matrix[i][2];
    A->matrix[i][1] = cos(angle) * temp_y + sin(angle) * temp_z;
    A->matrix[i][2] = -sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void rotation_by_oy(matrix_t *A, double angle) {
  angle = angle * M_PI / 180;
  for (int i = 1; i < A->rows; i++) {
    double temp_x = A->matrix[i][0];
    double temp_z = A->matrix[i][2];
    A->matrix[i][0] = cos(angle) * temp_x + sin(angle) * temp_z;
    A->matrix[i][2] = -sin(angle) * temp_x + cos(angle) * temp_z;
  }
}

void rotation_by_oz(matrix_t *A, double angle) {
  angle = angle * M_PI / 180;
  for (int i = 1; i < A->rows; i++) {
    double temp_x = A->matrix[i][0];
    double temp_y = A->matrix[i][1];
    A->matrix[i][0] = cos(angle) * temp_x + sin(angle) * temp_y;
    A->matrix[i][1] = -sin(angle) * temp_x + cos(angle) * temp_y;
  }
}

void scale_change(matrix_t *A, double scale) {
  for (int i = 1; i < A->rows; i++) {
    for (int j = 0; j < A->cols; j++) {
      A->matrix[i][j] *= scale;
    }
  }
}

void normalize(matrix_t *A, data_t *data) {
  double x_tmp = (data->maxX + data->minX) / 2;
  double y_tmp = (data->maxY + data->minY) / 2;
  double z_tmp = (data->maxZ + data->minZ) / 2;
  for (int i = 1; i < A->rows; i++) {
    A->matrix[i][0] -= x_tmp;
    A->matrix[i][1] -= y_tmp;
    A->matrix[i][2] -= z_tmp;
  }
  data->maxX -= x_tmp;
  data->maxY -= y_tmp;
  data->maxZ -= z_tmp;

  data->minX -= x_tmp;
  data->minY -= y_tmp;
  data->minZ -= z_tmp;
}