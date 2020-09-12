// 3rd Party
#include <QApplication>
#include <lv_examples/lv_examples.h>

// Local
#include "LvglContext.hpp"
#include "MainWindow.hpp"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  LvglContext  lvgl;
  MainWindow   window(lvgl);

  /// lvgl_sim_qt_example
  lv_demo_benchmark();

  window.show();
  return app.exec();
}
