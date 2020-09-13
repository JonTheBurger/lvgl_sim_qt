#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

// Standard
#include <memory>

// 3rd Party
#include <QMainWindow>
#include <QTimer>

// hello
namespace Ui {
class MainWindow;
}
class QGraphicsScene;
class MainWindow final : public QMainWindow {
  Q_OBJECT
  std::unique_ptr<Ui::MainWindow> ui_;
  QGraphicsScene*                 scene_;
  QTimer                          timer_;

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;
};

#endif  // MAINWINDOW_HPP
