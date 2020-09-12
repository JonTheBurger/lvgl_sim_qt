#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

// Standard
#include <memory>

// 3rd Party
#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}
class LvglContext;
class QGraphicsScene;
class MainWindow final : public QMainWindow {
  Q_OBJECT
  std::unique_ptr<Ui::MainWindow> ui_;
  QGraphicsScene*                 scene_;
  LvglContext&                    context_;
  QTimer                          timer_;

public:
  explicit MainWindow(LvglContext& context, QWidget* parent = nullptr);
  ~MainWindow() override;

private:
  void updateScene();
};

#endif  // MAINWINDOW_HPP
