#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QGraphicsView>
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <lv_conf.h>
#include <lvgl/lvgl.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT
  Ui::MainWindow* ui;
  QGraphicsScene* scene;
  QRgb            frameBuffer[LV_VER_RES_MAX][LV_HOR_RES_MAX]{};
  QImage          image;
  QPainter        painter;
  QPixmap         pixmap;
  QTimer          timer;

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  void flush(const lv_disp_drv_t* display_driver, const lv_area_t* area, const lv_color_t* color_p);

private:
  static constexpr int tick_period_ms = 100;

  Q_SIGNAL void sceneInvalidated();
  void          updateScene();
};

#endif  // MAINWINDOW_HPP
