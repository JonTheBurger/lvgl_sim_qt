#include <QApplication>
#include <lvgl/lvgl.h>

#include "MainWindow.hpp"

static lv_disp_buf_t display_buffer{};
static lv_color_t    buffer[LV_HOR_RES_MAX * LV_VER_RES_MAX]{};
static lv_disp_drv_t display_driver{};
static MainWindow*   window_handle;

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  MainWindow   window;
  window_handle = &window;

  lv_init();
  lv_disp_buf_init(&display_buffer, buffer, nullptr, sizeof(buffer) / sizeof(*buffer));
  lv_disp_drv_init(&display_driver);
  display_driver.buffer   = &display_buffer;
  display_driver.flush_cb = +[](lv_disp_drv_t* display_driver, const lv_area_t* area, lv_color_t* color_p) {
    window_handle->flush(display_driver, area, color_p);
    lv_disp_flush_ready(display_driver);
  };
  lv_disp_drv_register(&display_driver);

  lv_obj_t* label1 = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK); /*Break the long lines*/
  lv_label_set_recolor(label1, true);                  /*Enable re-coloring by commands in the text*/
  lv_label_set_align(label1, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
  lv_label_set_text(label1, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label "
                            "and  wrap long text automatically.");
  lv_obj_set_width(label1, 150);
  lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, -30);

  lv_obj_t* label2 = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(label2, LV_LABEL_LONG_SROLL_CIRC); /*Circular scroll*/
  lv_obj_set_width(label2, 150);
  lv_label_set_text(label2, "It is a circularly scrolling text. ");
  lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 30);

  window.show();
  return app.exec();
}
