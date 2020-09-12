// 3rd Party
#include <QApplication>
#include <lvgl/lvgl.h>

// Local
#include "LvglContext.hpp"
#include "MainWindow.hpp"

static void create_demo();

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  LvglContext  lvgl;
  MainWindow   window(lvgl);

  create_demo();

  window.show();
  return app.exec();
}

static void create_demo()
{
  static lv_obj_t* label1 = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK); /*Break the long lines*/
  lv_label_set_recolor(label1, true);                  /*Enable re-coloring by commands in the text*/
  lv_label_set_align(label1, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
  lv_label_set_text(label1, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label "
                            "and  wrap long text automatically.");
  lv_obj_set_width(label1, 150);
  lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, -30);

  static lv_obj_t* label2 = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(label2, LV_LABEL_LONG_SROLL_CIRC); /*Circular scroll*/
  lv_obj_set_width(label2, 150);
  lv_label_set_text(label2, "It is a circularly scrolling text. ");
  lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 30);
}
