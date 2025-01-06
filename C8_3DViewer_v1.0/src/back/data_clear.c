#include "3DViewer.h"

void data_clear(data_t *data) {
  data->maxX = -INFINITY;
  data->maxY = -INFINITY;
  data->maxZ = -INFINITY;

  data->minX = INFINITY;
  data->minY = INFINITY;
  data->minZ = INFINITY;
  if (data->matrix_3d.matrix != NULL) {
    free(data->matrix_3d.matrix);
  }
  for (unsigned int i = 0;
       i < data->count_facets + 1 && data->count_facets != 0; i++) {
    if (data->polygons[i].verts != NULL) {
      free(data->polygons[i].verts);
    }
  }
  if (data->polygons != NULL) {
    free(data->polygons);
  }
  data->count_facets = 0;
  data->count_verts = 0;
}
