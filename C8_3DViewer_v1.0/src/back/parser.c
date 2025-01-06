#include "parser.h"

int parser_start(char *file_name, data_t *data) {
  int status = 0;
  FILE *fp = NULL;
  fp = fopen(file_name, "rb");
  if (fp == NULL) {
    data->count_facets = 0;
    data->count_verts = 0;
    status = 1;

  } else {
    char line[4096] = {0};
    while ((fgets(line, 4096, fp)) != NULL && status == 0) {
      if (strlen(line) > 1 && line[0] == 'v' && line[1] == ' ') {
        data->count_verts += 1;
      } else if (strlen(line) > 1 && line[0] == 'f' && line[1] == ' ') {
        data->count_facets += 1;
      }
    }
    fclose(fp);
    data->polygons =
        (polygon_t *)calloc(data->count_facets + 1, sizeof(polygon_t));
    status = create_matrix(data->count_verts + 1, 3, &(data->matrix_3d));
    if (data->polygons == NULL) {
      status = 1;
    }
    fp = fopen(file_name, "rb");
    if (fp == NULL) {
      status = 1;

    } else if (data->count_verts == 0) {
      status = 1;

      fclose(fp);
    } else {
      status = parser_exec(fp, data);
      fclose(fp);
    }
  }
  return status;
}

int parser_exec(FILE *fp, data_t *data) {
  int status = 0;
  char line[4096] = {0};
  int i = 1;
  int ind = 1;
  while ((fgets(line, 4096, fp)) != NULL && status == 0) {
    if (strlen(line) > 1 && line[0] == 'v' && line[1] == ' ') {
      status = parser_verts(line, i, &(data->matrix_3d), data);
      i += 1;
    } else if (strlen(line) > 1 && line[0] == 'f' && line[1] == ' ') {
      status = create_polygons(line, data->polygons, ind);
      if (status == 0) {
        status = parser_facets(line, i, data->polygons, ind, data->count_verts);
        ind += 1;
      } else if (status == 2) {
        data->count_facets -= 1;
        status = 0;
      }
    }
  }
  return status;
}

int create_polygons(char *line, polygon_t *result, int ind) {
  int status = 0;
  line += 1;
  result[ind].verts_in_facets = check_count(line);
  if (result[ind].verts_in_facets < 2) {
    status = 2;
  } else {
    result[ind].verts = (int *)calloc(result[ind].verts_in_facets, sizeof(int));
    if (result[ind].verts == NULL) {
      status = 1;
    }
  }
  return status;
}

int parser_facets(char *line, int i, polygon_t *result, int ind,
                  unsigned int max_vert) {  //
  int status = 0;
  int i1 = 0;

  line += 1;
  if (check_line(line) == 0) {
    char copy[strlen(line) + 1];
    strcpy(copy, line);

    char *token = strtok(copy, " ");
    while (token != NULL && i1 < result[ind].verts_in_facets && status == 0) {
      if ((token[0] >= '0' && token[0] <= '9') || token[0] == '-') {
        status = number_add1(token, i1, i, result, ind, max_vert);
        token = strtok(NULL, " ");
        i1 += 1;
      } else {
        status = 1;
      }
    }
  } else {
    status = 1;
  }
  return status;
}

int number_add1(char *input, int i1, int i, polygon_t *result, int ind,
                unsigned int max_vert) {
  int status = 0;
  int count = 0;
  int value = 0;
  char number[256] = {0};
  while (digit_check(*input) == 1 || *input == '-') {
    number[count] = *input;
    count++;
    input += 1;
  }
  sscanf(number, "%d", &value);
  if (value < 0) {
    value = i + value;
  }
  if (value < 1 || value > (int)max_vert) {
    status = 1;
  } else {
    result[ind].verts[i1] = value;
  }

  return status;
}

int parser_verts(char *line, int i, matrix_t *result, data_t *data) {
  int status = 0;
  int j = 0;
  int step = 1;
  line += 1;
  if (check_count(line) == 3) {
    while (*line != '\0' && status == 0) {
      step = 1;
      if ((*line >= '0' && *line <= '9') || *line == '-') {
        step = number_add(line, i, j, result, data);
        j += 1;
      } else if (*line == '/') {
        status = 1;
      }
      line += step;
    }
  } else {
    status = 1;
  }
  return status;
}

int number_add(char *input, int i, int j, matrix_t *result, data_t *data) {
  int count = 0;
  double value = 0;
  char number[256] = {0};
  while (digit_check(*input) == 1 || *input == '.' || *input == '-') {
    number[count] = *input;
    count++;
    input += 1;
  }
  sscanf(number, "%lf", &value);
  if (j == 0 && value > data->maxX) {
    data->maxX = value;
  } else if (j == 1 && value > data->maxY) {
    data->maxY = value;
  } else if (j == 2 && value > data->maxZ) {
    data->maxZ = value;
  } else if (j == 0 && value < data->minX) {
    data->minX = value;
  } else if (j == 1 && value < data->minY) {
    data->minY = value;
  } else if (j == 2 && value < data->minZ) {
    data->minZ = value;
  }
  result->matrix[i][j] = value;
  return count;
}
// проверка символа на число
int digit_check(char symb) {
  int status = 0;
  if (47 < symb && symb < 58) {
    status = 1;
  }
  return status;
}

int check_count(char *str) {
  int count = 0;

  char copy[strlen(str) + 1];
  strcpy(copy, str);

  char *token = strtok(copy, " ");
  while (token != NULL) {
    if ((token[0] >= '0' && token[0] <= '9') || token[0] == '-') {
      count++;
    }
    token = strtok(NULL, " ");
  }
  return count;
}

int check_line(char *str) {
  int status = 0;
  while (*str != '\0') {
    if ((*str < '0' || *str > '9') && *str != ' ' && *str != '\n' &&
        *str != '.' && *str != '-' && *str != '/' && *str > 31) {
      status = 1;
    }
    str += 1;
  }
  return status;
}
