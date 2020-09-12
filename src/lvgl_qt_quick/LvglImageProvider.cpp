#include "LvglImageProvider.hpp"

LvglImageProvider::LvglImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
    , display_buffer{}
    , display_driver{}
    , display_frames{}
    , current_frame{}
    , image(reinterpret_cast<uint8_t*>(current_frame),
            sizeof(*current_frame) / sizeof(**current_frame),
            sizeof(current_frame) / sizeof(*current_frame),
            QImage::Format_RGB32)
{
  lv_init();
  lv_disp_buf_init(&display_buffer, display_frames[0], display_frames[1], sizeof(display_frames[0]) / sizeof(*display_frames[0]));
  lv_disp_drv_init(&display_driver);
  display_driver.buffer   = &display_buffer;
  display_driver.flush_cb = +[](lv_disp_drv_t* display_driver, const lv_area_t* area, lv_color_t* color_p) {
    auto* screen = static_cast<LvglImageProvider*>(display_driver->user_data);
    screen->flush(display_driver, area, color_p);
    lv_disp_flush_ready(display_driver);
  };
  display_driver.user_data = this;
  lv_disp_drv_register(&display_driver);
}

void LvglImageProvider::flush(const lv_disp_drv_t*, const lv_area_t* area, const lv_color_t* color_p)
{
  for (auto y = area->y1; y <= area->y2; ++y)
  {
    for (auto x = area->x1; x <= area->x2; ++x)
    {
      current_frame[y][x] = color_p->full;
      ++color_p;
    }
  }
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
QPixmap LvglImageProvider::requestPixmap(const QString&, QSize* size, const QSize& requestedSize, const QQuickImageProviderOptions&)
#else
QPixmap LvglImageProvider::requestPixmap(const QString&, QSize* size, const QSize& requestedSize)
#endif
{
  if (size != nullptr)
  {
    *size = { LV_HOR_RES_MAX, LV_VER_RES_MAX };
  }

  lv_tick_inc(tick_period_ms);
  lv_task_handler();

  return QPixmap::fromImage(image).scaled(
    requestedSize.width() > 0 ? requestedSize.width() : LV_HOR_RES_MAX,
    requestedSize.height() > 0 ? requestedSize.height() : LV_VER_RES_MAX);
}
