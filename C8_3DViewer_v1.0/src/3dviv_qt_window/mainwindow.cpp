#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setWindowTitle("3dViv");

  ui->setupUi(this);
  connect(&tmr, SIGNAL(timeout()), this, SLOT(make_gif()));

  readJson();
}

MainWindow::~MainWindow() {
  data_clear(&ui->widget->data_info);
  writeJson();
  delete gif_pointer;
  delete ui;
}

void MainWindow::readJson() {
  QString json;
  QFile file_json("settings.json");
  if (file_json.open(QIODevice::ReadOnly)) {
    json = file_json.readAll();
    file_json.close();
  }

  Document document;

  if (!document.Parse(json.toStdString().c_str()).HasParseError()) {
    if (document.IsObject()) {
      if (document.HasMember("redColLine")) {
        if (document["redColLine"].IsNumber()) {
          ui->widget->redColLine = document["redColLine"].GetFloat();
        }
      }
      if (document.HasMember("greenColLine")) {
        if (document["redColLine"].IsNumber()) {
          ui->widget->greenColLine = document["greenColLine"].GetFloat();
        }
      }
      if (document.HasMember("blueColLine")) {
        if (document["redColLine"].IsNumber()) {
          ui->widget->blueColLine = document["blueColLine"].GetFloat();
        }
      }
      if (document.HasMember("lines_type")) {
        if (document["lines_type"].IsNumber()) {
          ui->widget->lines_type = document["lines_type"].GetFloat();
        }
      }
      if (document.HasMember("lines_width")) {
        if (document["lines_width"].IsNumber()) {
          ui->widget->lines_width = document["lines_width"].GetFloat();
          ui->lines_widthSpinBox->setValue(ui->widget->lines_width);
        }
      }

      if (document.HasMember("redColPoint")) {
        if (document["redColPoint"].IsNumber()) {
          ui->widget->redColPoint = document["redColPoint"].GetFloat();
        }
      }
      if (document.HasMember("greenColPoint")) {
        if (document["redColPoint"].IsNumber()) {
          ui->widget->greenColPoint = document["greenColPoint"].GetFloat();
        }
      }
      if (document.HasMember("blueColPoint")) {
        if (document["redColPoint"].IsNumber()) {
          ui->widget->blueColPoint = document["blueColPoint"].GetFloat();
        }
      }
      if (document.HasMember("pointer_type")) {
        if (document["pointer_type"].IsNumber()) {
          ui->widget->pointer_type = document["pointer_type"].GetFloat();
        }
      }
      if (document.HasMember("pointer_width")) {
        if (document["pointer_width"].IsNumber()) {
          ui->widget->pointer_width = document["pointer_width"].GetFloat();
          ui->points_widthSpinBox->setValue(ui->widget->pointer_width);
        }
      }

      if (document.HasMember("redColBack")) {
        if (document["redColBack"].IsNumber()) {
          ui->widget->redColBack = document["redColBack"].GetFloat();
        }
      }
      if (document.HasMember("greenColBack")) {
        if (document["redColBack"].IsNumber()) {
          ui->widget->greenColBack = document["greenColBack"].GetFloat();
        }
      }
      if (document.HasMember("blueColBack")) {
        if (document["redColBack"].IsNumber()) {
          ui->widget->blueColBack = document["blueColBack"].GetFloat();
        }
      }
      if (document.HasMember("alphaColBack")) {
        if (document["alphaColBack"].IsNumber()) {
          ui->widget->alphaColBack = document["alphaColBack"].GetFloat();
        }
      }

      if (document.HasMember("projection_type")) {
        if (document["projection_type"].IsNumber()) {
          ui->widget->projection_type = document["projection_type"].GetFloat();
        }
      }
    }
  } else {
  }
}

void MainWindow::writeJson() {
  QJsonObject recordObject;

  recordObject.insert("redColLine",
                      QJsonValue::fromVariant(ui->widget->redColLine));
  recordObject.insert("greenColLine",
                      QJsonValue::fromVariant(ui->widget->greenColLine));
  recordObject.insert("blueColLine",
                      QJsonValue::fromVariant(ui->widget->blueColLine));

  recordObject.insert("lines_type",
                      QJsonValue::fromVariant(ui->widget->lines_type));
  recordObject.insert("lines_width",
                      QJsonValue::fromVariant(ui->widget->lines_width));

  recordObject.insert("redColPoint",
                      QJsonValue::fromVariant(ui->widget->redColPoint));
  recordObject.insert("greenColPoint",
                      QJsonValue::fromVariant(ui->widget->greenColPoint));
  recordObject.insert("blueColPoint",
                      QJsonValue::fromVariant(ui->widget->blueColPoint));

  recordObject.insert("pointer_type",
                      QJsonValue::fromVariant(ui->widget->pointer_type));
  recordObject.insert("pointer_width",
                      QJsonValue::fromVariant(ui->widget->pointer_width));

  recordObject.insert("redColBack",
                      QJsonValue::fromVariant(ui->widget->redColBack));
  recordObject.insert("greenColBack",
                      QJsonValue::fromVariant(ui->widget->greenColBack));
  recordObject.insert("blueColBack",
                      QJsonValue::fromVariant(ui->widget->blueColBack));

  recordObject.insert("projection_type",
                      QJsonValue::fromVariant(ui->widget->projection_type));

  QJsonDocument doc(recordObject);
  QString jsonString = doc.toJson(QJsonDocument::Indented);

  //Записываем данные в файл
  QFile file;
  file.setFileName("settings.json");
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream stream(&file);
  stream << jsonString;
  file.close();
}

void MainWindow::on_right_btn_clicked() {
  if (err_file == 0) {
    move_x(&ui->widget->data_info.matrix_3d,
           ui->move_spinBox->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_left_btn_clicked() {
  if (err_file == 0) {
    move_x(&ui->widget->data_info.matrix_3d,
           -ui->move_spinBox->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_up_btn_clicked() {
  if (err_file == 0) {
    move_y(&ui->widget->data_info.matrix_3d,
           ui->move_spinBox->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_down_btn_clicked() {
  if (err_file == 0) {
    move_y(&ui->widget->data_info.matrix_3d,
           -ui->move_spinBox->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_z_up_btn_clicked() {
  if (err_file == 0) {
    move_z(&ui->widget->data_info.matrix_3d,
           ui->move_spinBox->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_z_down_btn_clicked() {
  if (err_file == 0) {
    move_z(&ui->widget->data_info.matrix_3d,
           -ui->move_spinBox->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_rot_ox_pl_btn_clicked() {
  if (err_file == 0) {
    rotation_by_ox(&ui->widget->data_info.matrix_3d,
                   ui->spinBox_angle->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_rot_ox_min_btn_clicked() {
  if (err_file == 0) {
    rotation_by_ox(&ui->widget->data_info.matrix_3d,
                   -ui->spinBox_angle->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_rot_oy_pl_btn_clicked() {
  if (err_file == 0) {
    rotation_by_oy(&ui->widget->data_info.matrix_3d,
                   ui->spinBox_angle->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_rot_oy_min_btn_clicked() {
  if (err_file == 0) {
    rotation_by_oy(&ui->widget->data_info.matrix_3d,
                   -ui->spinBox_angle->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_rot_oz_pl_btn_clicked() {
  if (err_file == 0) {
    rotation_by_oz(&ui->widget->data_info.matrix_3d,
                   ui->spinBox_angle->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_rot_oz_min_btn_clicked() {
  if (err_file == 0) {
    rotation_by_oz(&ui->widget->data_info.matrix_3d,
                   -ui->spinBox_angle->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_actionOpen_triggered() {
  QString file_name =
      QFileDialog::getOpenFileName(this, "text", 0, "Text Files (*.obj)");

  if (file_name != "") {
    ui->statusbar->showMessage(file_name);
    char *cstr;
    QByteArray cppstr = file_name.toUtf8();
    cstr = cppstr.data();
    data_clear(&ui->widget->data_info);
    err_file = parser_start(cstr, &(ui->widget->data_info));
    if (err_file == 0) {
      ui->widget->data_info.status = 0;
      ui->number_of_verts->setText(
          QString::number(ui->widget->data_info.count_verts));
      ui->number_of_facets->setText(
          QString::number(ui->widget->data_info.count_facets));

      normalize(&(ui->widget->data_info.matrix_3d), &(ui->widget->data_info));

      ui->widget->far = fmax(fabs(ui->widget->data_info.maxY), fabs(ui->widget->data_info.minY))  + fmax(fabs(ui->widget->data_info.maxZ), fabs(ui->widget->data_info.minZ));
    } else {
      ui->widget->data_info.status = 1;
      ui->number_of_verts->setText("0");
      ui->number_of_facets->setText("0");
      QMessageBox::critical(this, "Status", "Errow while parsing");
    }
  }
}

void MainWindow::on_pushButton_clicked() {
  if (err_file == 0) {
    double scale = 1.0 + ui->scale_spinBox->text().toDouble();
    scale_change(&ui->widget->data_info.matrix_3d, scale);
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_2_clicked() {
  if (err_file == 0) {
    double scale = 1.0 - ui->scale_spinBox->text().toDouble();
    scale_change(&ui->widget->data_info.matrix_3d, scale);
    ui->widget->update();
  }
}

void MainWindow::on_actionDashed_triggered() {
    ui->widget->lines_type = 1;
  if (err_file == 0) {
    ui->widget->update();
  }
}

void MainWindow::on_actionSolid_triggered() {
    ui->widget->lines_type = 0;
  if (err_file == 0) {
    ui->widget->update();
  }
}

void MainWindow::on_actionLineColor_triggered() {

    QColor color = QColorDialog::getColor(Qt::white, this, "Select color");
    ui->widget->redColLine = color.redF();
    ui->widget->greenColLine = color.greenF();
    ui->widget->blueColLine = color.blueF();
    if (err_file == 0) {
    ui->widget->update();
  }
}

void MainWindow::on_lines_widthSpinBox_textChanged() {

    ui->widget->lines_width = ui->lines_widthSpinBox->text().toDouble();
  if (err_file == 0) {
    ui->widget->update();
  }
}

void MainWindow::on_actionNone_triggered() {

    ui->widget->pointer_type = 0;
  if (err_file == 0) {
    ui->widget->update();
  }
}

void MainWindow::on_actionSquare_triggered() {
    ui->widget->pointer_type = 1;
    if (err_file == 0) {
    ui->widget->update();
  }
}

void MainWindow::on_actionSmooth_triggered() {

    ui->widget->pointer_type = 2;
  if (err_file == 0) {
    ui->widget->update();
  }
}

void MainWindow::on_actionColorPointer_triggered() {

    QColor color = QColorDialog::getColor(Qt::white, this, "Select color");
    ui->widget->redColPoint = color.redF();
    ui->widget->greenColPoint = color.greenF();
    ui->widget->blueColPoint = color.blueF();
if (err_file == 0) {
    ui->widget->update();
  }
}

void MainWindow::on_points_widthSpinBox_textChanged() {
    ui->widget->pointer_width = ui->points_widthSpinBox->text().toDouble();
  if (err_file == 0) {
    ui->widget->update();
  }
}

void MainWindow::on_background_color_clicked() {

    QColor color = QColorDialog::getColor(Qt::white, this, "Select color");
    ui->widget->redColBack = color.redF();
    ui->widget->greenColBack = color.greenF();
    ui->widget->blueColBack = color.blueF();
    ui->widget->alphaColBack = color.alphaF();
    if (err_file == 0) {
    ui->widget->update();
  }
}

void MainWindow::on_parallel_projec_btn_clicked() {

    ui->widget->projection_type = 0;
  if (err_file == 0) {
    ui->widget->update();
  }
}

void MainWindow::on_centre_projec_btn_clicked() {
    ui->widget->projection_type = 1;
  if (err_file == 0) {
    ui->widget->update();
  }
}

void MainWindow::on_actionMake_img_triggered() {
  if (err_file == 0) {
    QString file = QFileDialog::getSaveFileName(
        this, "Save as...", "name", "BMP (*.bmp);; JPEG (*.jpg *.jpeg)");
    QImage img = ui->widget->grabFramebuffer();
    img.save(file);
  }
}

void MainWindow::on_actionMake_gif_triggered() {
  if (err_file == 0) {
    tmr.start(100);
  }
}

void MainWindow::make_gif() {
  if (err_file == 0) {
    if (gif_pointer == NULL) {
      gif_pointer = new QGifImage;
      QGifImage gif_pointer(QSize(640, 480));
    }
    QImage img = ui->widget->grabFramebuffer();
    gif_pointer->addFrame(img, 100);
    if (gif_pointer->frameCount() == 50) {
      QString file = QFileDialog::getSaveFileName(this, "Save as...", "name",
                                                  "Images (*.gif)");
      gif_pointer->save(file);
      delete gif_pointer;
      gif_pointer = NULL;
      tmr.stop();
      QMessageBox::about(this, "Status", "GIF is done");
    }
  }
}
