#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <gl.h>
#include <glu.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "../back/3DViewer.h"
int create_matrix(int rows, int cols, matrix_t *result);
void move_x(matrix_t *A, double a);
void move_y(matrix_t *A, double a);
void move_z(matrix_t *A, double a);

void rotation_by_ox(matrix_t *A, double angle);
void rotation_by_oy(matrix_t *A, double angle);
void rotation_by_oz(matrix_t *A, double angle);

void scale_change(matrix_t *A, double scale);
#ifdef __cplusplus
}
#endif

class glWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    glWidget(QWidget *parent = nullptr);
    data_t data_info;

    double far = 0;

    float redColLine = 0;
    float greenColLine = 0;
    float blueColLine = 1;

    int lines_type = 0;
    float lines_width = 8;

    float redColPoint = 1;
    float greenColPoint = 0;
    float blueColPoint = 0;

    int pointer_type = 2;
    float pointer_width = 10;

    float redColBack = 0;
    float greenColBack = 0;
    float blueColBack = 0;
    float alphaColBack = 0;

    int projection_type = 1;
    void resizeGL(int w, int h);

private:
    float xRot, yRot, zRot;
    QPoint mPos;
    QString file_name;
    void drawSkeleton(data_t data_info);
    void initializeGL();
    void paintGL();
};
#endif // GLWIDGET_H
