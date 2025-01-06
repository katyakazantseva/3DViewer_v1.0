#ifndef TRI_DVIEWER_H
#define TRI_DVIEWER_H

typedef struct Matrix {
  double **matrix;
  int rows;
  int cols;
} matrix_t;

typedef struct facets {
  int *verts;
  int verts_in_facets;
} polygon_t;

typedef struct data {
  unsigned int count_verts;   // количество вершин
  unsigned int count_facets;  // количество полигонов
  double maxX;
  double maxY;
  double maxZ;
  double minX;
  double minY;
  double minZ;
  int status;
  matrix_t matrix_3d;
  polygon_t *polygons;
} data_t;

#ifdef __linux__

#define M_PI 3.14159265358979323846264338327950288

#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

// Создание матриц (create_matrix)
int create_matrix(int rows, int cols, matrix_t *result);
// проверка символа на число
int digit_check(char symb);
int number_add(char *input, int i, int j, matrix_t *result, data_t *data);

// Аффины
void move_x(matrix_t *A, double a);
void move_y(matrix_t *A, double a);
void move_z(matrix_t *A, double a);

void rotation_by_ox(matrix_t *A, double angle);
void rotation_by_oy(matrix_t *A, double angle);
void rotation_by_oz(matrix_t *A, double angle);
void scale_change(matrix_t *A, double scale);

void data_clear(data_t *data);
void normalize(matrix_t *A, data_t *data);

#define OK 0
#define INCORECT 1

#endif
