#ifndef PARSER_H
#define PARSER_H

#include "3DViewer.h"

int parser_start(char *file_name, data_t *data);
int parser_exec(FILE *fp, data_t *data);

int parser_verts(char *line, int i, matrix_t *result, data_t *data);
int check_count(char *line);
int check_line(char *str);

int parser_facets(char *line, int i, polygon_t *result, int ind,
                  unsigned int max_vert);
int create_polygons(char *line, polygon_t *result, int ind);
int number_add1(char *input, int i1, int i, polygon_t *result, int ind,
                unsigned int max_vert);
#endif
