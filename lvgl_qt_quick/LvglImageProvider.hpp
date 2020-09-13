#ifndef LVGLIMAGEPROVIDER_HPP
#define LVGLIMAGEPROVIDER_HPP

// 3rd Party
#include <QQuickImageProvider>
#include <lvgl/lvgl.h>

class LvglRenderer;
class LvglImageProvider final : public QQuickImageProvider {
  LvglRenderer&  renderer_;
  QObject*       mouse_area_;
  lv_indev_drv_t mouse_driver_;
  lv_indev_t*    mouse_device_;

public:
  LvglImageProvider(LvglRenderer& renderer);

  void        setMouseArea(QObject* mouse_area);
  QPointF     mousePosition() const;
  bool        isMousePressed() const noexcept;

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize, const QQuickImageProviderOptions& options) override;
#else
  QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize) override;
#endif
};

#endif // LVGLIMAGEPROVIDER_HPP
