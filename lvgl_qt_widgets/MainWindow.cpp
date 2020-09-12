// 3rd Party
#include <QGraphicsItem>
#include <QGraphicsScene>

// Local
#include "LvglContext.hpp"
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(LvglContext& context, QWidget* parent)
    : QMainWindow(parent)
    , ui_{ std::make_unique<Ui::MainWindow>() }
    , scene_{ new QGraphicsScene(this) }
    , context_{ context }
    , timer_()
{
  ui_->setupUi(this);
  ui_->graphicsView->setScene(scene_);
  connect(&timer_, &QTimer::timeout, [this]() {
    lv_tick_inc(LvglContext::Tick_Period_Ms);
    lv_task_handler();
    this->updateScene();
  });
  timer_.setInterval(LvglContext::Tick_Period_Ms);
  timer_.start();
}

MainWindow::~MainWindow() = default;

void MainWindow::updateScene()
{
  scene_->clear();
  const QGraphicsItem* item = scene_->addPixmap(context_.pixmap());
  ui_->graphicsView->fitInView(item, Qt::AspectRatioMode::KeepAspectRatio);
}
