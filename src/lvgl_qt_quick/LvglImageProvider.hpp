#ifndef LVGLIMAGEPROVIDER_HPP
#define LVGLIMAGEPROVIDER_HPP

#include <QPixmap>
#include <QQuickImageProvider>
#include <QTimer>
#include <lvgl/lvgl.h>

class LvglImageProvider final : public QQuickImageProvider {
  lv_disp_buf_t display_buffer;
  lv_disp_drv_t display_driver;
  lv_color_t    display_frames[2][LV_HOR_RES_MAX * LV_VER_RES_MAX];
  uint32_t      current_frame[LV_VER_RES_MAX][LV_HOR_RES_MAX];
  QImage        image;

public:
  static constexpr int tick_period_ms = 100;

  LvglImageProvider();
  void flush(const lv_disp_drv_t* display_driver, const lv_area_t* area, const lv_color_t* color_p);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize, const QQuickImageProviderOptions& options) override;
#else
  QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize) override;
#endif
};

#endif // LVGLIMAGEPROVIDER_HPP
