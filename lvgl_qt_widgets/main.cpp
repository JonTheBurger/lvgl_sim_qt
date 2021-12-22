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

  auto* default_group = lv_group_create();
  lv_group_set_default(default_group);
  lv_indev_set_group(window.view().keyboardDevice(), default_group);

  /// lvgl_sim_qt_example
  lv_demo_widgets();
  //    lv_demo_stress();
  //    lv_demo_benchmark();
  //    lv_demo_music();
  //    lv_example_style_14();
  //  lv_example_get_started_3();

  window.show();
  return app.exec();
}
