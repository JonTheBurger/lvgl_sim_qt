// 3rd Party
#include <QApplication>
#include <lv_examples/lv_examples.h>

// Local
#include "LvglRenderer.hpp"
#include "MainWindow.hpp"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  MainWindow   window;

  /// lvgl_sim_qt_example
  lv_demo_widgets();

  window.show();
  return app.exec();
}
