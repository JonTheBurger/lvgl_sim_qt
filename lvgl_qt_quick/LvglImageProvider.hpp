#ifndef LVGLIMAGEPROVIDER_HPP
#define LVGLIMAGEPROVIDER_HPP

// 3rd Party
#include <QQuickImageProvider>
#include <lvgl.h>

class LvglRenderer;
class LvglImageProvider final :

#if QT_VERSION < 0x060000
    public QObject,
#endif

public QQuickImageProvider {
  Q_OBJECT

  LvglRenderer&  renderer_;
  QObject*       mouse_area_;
  Qt::Key        key_;
  lv_indev_drv_t mouse_driver_;
  lv_indev_drv_t keyboard_driver_;
  lv_indev_t*    mouse_device_;
  lv_indev_t*    keyboard_device_;

public:
  explicit LvglImageProvider(LvglRenderer& renderer);

  QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize) override;
  void    setMouseArea(QObject* mouse_area);
  QPointF mousePosition() const;
  bool    isMousePressed() const noexcept;
  Qt::Key key() const noexcept;

public slots:
  void onKeyEvent(Qt::Key key, bool is_pressed);
};

#endif  // LVGLIMAGEPROVIDER_HPP
