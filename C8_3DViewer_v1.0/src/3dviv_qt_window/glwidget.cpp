#include "glwidget.h"

glWidget::glWidget(QWidget *parent) : QOpenGLWidget(parent) {
  setWindowTitle("3dViv");
  data_info = {0, 0, -INFINITY, -INFINITY, -INFINITY, INFINITY, INFINITY, INFINITY, 1, {NULL, 0, 0}, NULL};
}

void glWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
}
void glWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
}
void glWidget::paintGL() {
  if (data_info.status == 0) {

  glClearColor(redColBack, greenColBack, blueColBack, alphaColBack);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection_type) {
    glFrustum(-1, 1, -1, 1, 1, 99999999);
  } else {
    glOrtho(-1, 1, -1, 1, 1, 99999999);
    float value = 0.5 / fabs(data_info.maxY);
    glScalef(value, value, 1.0f);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslated(0, 0, -far);
  drawSkeleton(data_info);
  }
}

void glWidget::drawSkeleton(data_t data_info) {
  int index = 0;

  float *ver_array = (float *)calloc(
      data_info.matrix_3d.cols * data_info.matrix_3d.rows, sizeof(float));
  if (ver_array != NULL) {
  for (int i = 1; i < data_info.matrix_3d.rows; i++) {
    for (int j = 0; j < data_info.matrix_3d.cols; j++) {
      ver_array[index] = data_info.matrix_3d.matrix[i][j];
      index += 1;
    }
  }

  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, ver_array);

  glColor3f(redColPoint, greenColPoint, blueColPoint);
  glPointSize(pointer_width);
  if (pointer_type == 2) {
    glEnable(GL_POINT_SMOOTH);
  }
  if (pointer_type) {
    glDrawArrays(GL_POINTS, 0, data_info.count_verts);
  }

  glColor3f(redColLine, greenColLine, blueColLine);
  glLineWidth(lines_width);
  if (lines_type) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00ff);
  }

  GLuint indexes_array[2] = {0};
  for (unsigned int i = 1; i < data_info.count_facets; i++) {
    for (int j = 0; j < data_info.polygons[i].verts_in_facets - 1; j++) {
      indexes_array[0] = data_info.polygons[i].verts[j] - 1;
      indexes_array[1] = data_info.polygons[i].verts[j + 1] - 1;
      glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, indexes_array);
    }
    indexes_array[0] =
        data_info.polygons[i].verts[data_info.polygons[i].verts_in_facets - 1] -
        1;
    indexes_array[1] = data_info.polygons[i].verts[0] - 1;
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, indexes_array);
  }

  if (lines_type) {
    glDisable(GL_LINE_STIPPLE);
  }
  glDisableClientState(GL_VERTEX_ARRAY);
  if (pointer_type == 2) {
    glDisable(GL_POINT_SMOOTH);
  }
  }
  if (ver_array != NULL) {
  free(ver_array);
  }
}
