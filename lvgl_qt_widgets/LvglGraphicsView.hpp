#ifndef LVGLGRAPHICSVIEW_HPP
#define LVGLGRAPHICSVIEW_HPP

// 3rd Party
#include <QGraphicsView>
#include <lvgl/lvgl.h>

// Local
#include "LvglRenderer.hpp"

class LvglRenderer;
class LvglGraphicsView final : public QGraphicsView {
  LvglRenderer   renderer_;
  lv_indev_drv_t keyboard_driver_;
  lv_indev_drv_t mouse_driver_;
  lv_indev_t*    keyboard_device_;
  lv_indev_t*    mouse_device_;
  Qt::Key        key_;
  bool           is_mouse_pressed_;

public:
  LvglGraphicsView(QWidget* parent = nullptr);
  LvglGraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);

  void        tick();
  lv_indev_t* keyboardDevice();
  Qt::Key     key() const noexcept;
  QPointF     mousePosition() const;
  bool        isMousePressed() const noexcept;

private:
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
};

#endif // LVGLGRAPHICSVIEW_HPP
