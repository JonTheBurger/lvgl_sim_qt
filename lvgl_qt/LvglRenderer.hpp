#ifndef LVGLRENDERER_HPP
#define LVGLRENDERER_HPP

// Standard
#include <cstddef>
#include <cstdint>

// 3rd Party
#include <QImage>
#include <QPixmap>
#include <lvgl.h>

#if (LV_COLOR_DEPTH == 32)
#  define LVGL_SIM_QT_LVGL_RENDERER_IMAGE_FORMAT (QImage::Format_ARGB32)
#elif ((LV_COLOR_DEPTH == 16) && (LV_COLOR_16_SWAP == 0))
#  define LVGL_SIM_QT_LVGL_RENDERER_IMAGE_FORMAT (QImage::Format_RGB16)
#else
#  define LVGL_SIM_QT_LVGL_RENDERER_IMAGE_FORMAT (QImage::Format_Indexed8)
#endif

class LvglRenderer {
public:
  static constexpr QImage::Format Image_Format   = LVGL_SIM_QT_LVGL_RENDERER_IMAGE_FORMAT;
  static constexpr int            Tick_Period_Ms = 16;
  static constexpr size_t         Max_Width      = 640;  ///< in pixels
  static constexpr size_t         Max_Height     = 360;  ///< in pixels
  /// 1 Screen Size to N Display Buffer Size ratio. [LVGL recommends one tenth](https://docs.lvgl.io/latest/en/html/get-started/quick-overview.html#add-lvgl-into-your-project)
  static constexpr size_t Display_Buffer_Ratio = 10;

private:
  lv_color_t         display_frame1_[Max_Width * Max_Height / Display_Buffer_Ratio];
  lv_color_t         display_frame2_[Max_Width * Max_Height / Display_Buffer_Ratio];
  lv_color_t         current_frame_[Max_Height][Max_Width];
  lv_disp_draw_buf_t display_buffer_;
  lv_disp_drv_t      display_driver_;
  QImage             image_;

public:
  LvglRenderer();
  void            flush(const lv_disp_drv_t* display_driver, const lv_area_t* area, const lv_color_t* colors) noexcept;
  QPixmap         pixmap() const;
  static uint32_t toAscii(Qt::Key key);
};

#endif  // LVGLRENDERER_HPP
