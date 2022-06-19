// Local
#include "MainWindow.hpp"

#include "LvglRenderer.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui_{ std::make_unique<Ui::MainWindow>() }
    , scene_{ new QGraphicsScene(this) }
    , timer_()
{
  ui_->setupUi(this);
  resize(LvglRenderer::Max_Width, LvglRenderer::Max_Height);
  ui_->graphicsView->setScene(scene_);
  connect(&timer_, &QTimer::timeout, ui_->graphicsView, &LvglGraphicsView::tick);
  timer_.setInterval(LvglRenderer::Tick_Period_Ms);
  timer_.start();
}

LvglGraphicsView& MainWindow::view()
{
  return *ui_->graphicsView;
}

MainWindow::~MainWindow() = default;
