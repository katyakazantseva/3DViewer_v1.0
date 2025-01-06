#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QTimer>
#include <QMessageBox>
#include "glwidget.h"

#include <QFile>
#include "gifimage/gifimage/qgifimage.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "../back/parser.h"
int parser_start(char *file_name, data_t *data);
void normalize(matrix_t *A, data_t *data);
void data_clear(data_t *data);
#ifdef __cplusplus
}
#endif


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace rapidjson;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readJson();
    void writeJson();

private slots:
    void on_right_btn_clicked();

    void on_left_btn_clicked();

    void on_up_btn_clicked();

    void on_down_btn_clicked();

    void on_z_up_btn_clicked();

    void on_z_down_btn_clicked();

    void on_rot_ox_pl_btn_clicked();

    void on_rot_ox_min_btn_clicked();

    void on_rot_oy_pl_btn_clicked();

    void on_rot_oy_min_btn_clicked();

    void on_rot_oz_pl_btn_clicked();

    void on_rot_oz_min_btn_clicked();

    void on_actionOpen_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionDashed_triggered();

    void on_actionSolid_triggered();

    void on_actionLineColor_triggered();

    void on_lines_widthSpinBox_textChanged();

    void on_actionNone_triggered();

    void on_actionSquare_triggered();

    void on_actionSmooth_triggered();

    void on_actionColorPointer_triggered();

    void on_points_widthSpinBox_textChanged();

    void on_background_color_clicked();

    void on_parallel_projec_btn_clicked();

    void on_centre_projec_btn_clicked();

    void on_actionMake_img_triggered();

    void on_actionMake_gif_triggered();

    void make_gif();

private:
    Ui::MainWindow *ui;
    QTimer tmr;
    QGifImage *gif_pointer = NULL;
    int err_file = 1;
};
#endif // MAINWINDOW_H
