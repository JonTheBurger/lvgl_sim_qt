#include "MainWindow.hpp"

#include <QGraphicsItem>

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , image(reinterpret_cast<uint8_t*>(frameBuffer),
            sizeof(*frameBuffer) / sizeof(**frameBuffer),
            sizeof(frameBuffer) / sizeof(*frameBuffer),
            QImage::Format_RGB32)
    , timer()
{
  ui->setupUi(this);
  ui->graphicsView->setScene(scene);
  connect(&timer, &QTimer::timeout, [this]() {
    lv_tick_inc(tick_period_ms);
    lv_task_handler();
    this->updateScene();
  });
  timer.setInterval(tick_period_ms);
  timer.start();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::flush(const lv_disp_drv_t*, const lv_area_t* area, const lv_color_t* color_p)
{
  for (auto y = area->y1; y <= area->y2; ++y)
  {
    for (auto x = area->x1; x <= area->x2; ++x)
    {
      frameBuffer[y][x] = color_p->full;
      ++color_p;
    }
  }
}

void MainWindow::updateScene()
{
  scene->clear();
  const QGraphicsItem* item = scene->addPixmap(QPixmap::fromImage(image));
  ui->graphicsView->fitInView(item, Qt::AspectRatioMode::KeepAspectRatio);
}
