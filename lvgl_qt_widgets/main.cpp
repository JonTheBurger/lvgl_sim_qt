// 3rd Party
#include <QApplication>
#include <lv_demo.h>
#include <lv_examples.h>

// Local
#include "LvglRenderer.hpp"
#include "MainWindow.hpp"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  MainWindow   window;

  /// Uncomment one of the following for a demo
  lv_demo_widgets();
  // lv_demo_stress();
  // lv_demo_benchmark();
  // lv_demo_music();

  window.show();
  return app.exec();
}
