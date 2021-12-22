// 3rd Party
#include <QObject>

// Local
#include "LvglRenderer.hpp"
#include "LvglImageProvider.hpp"

static void mouseRead(lv_indev_drv_t* device, lv_indev_data_t* data);

LvglImageProvider::LvglImageProvider(LvglRenderer& renderer)
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
    , renderer_{ renderer }
    , mouse_area_{ nullptr }
    , mouse_driver_{}
    , mouse_device_{ nullptr }
{
  lv_indev_drv_init(&mouse_driver_);
  mouse_driver_.type      = LV_INDEV_TYPE_POINTER;
  mouse_driver_.user_data = this;
  mouse_driver_.read_cb   = &mouseRead;
  mouse_device_           = lv_indev_drv_register(&mouse_driver_);
}

QPixmap LvglImageProvider::requestPixmap(const QString&, QSize* size, const QSize& requestedSize)
{
  if (size != nullptr)
  {
    *size = { LvglRenderer::Max_Width, LvglRenderer::Max_Height };
  }

  lv_tick_inc(LvglRenderer::Tick_Period_Ms);
  lv_task_handler();

  return renderer_.pixmap().scaled(
    requestedSize.width() > 0 ? requestedSize.width() : LvglRenderer::Max_Width,
    requestedSize.height() > 0 ? requestedSize.height() : LvglRenderer::Max_Height);
}

void LvglImageProvider::setMouseArea(QObject* mouse_area)
{
  mouse_area_ = mouse_area;
}

QPointF LvglImageProvider::mousePosition() const
{
  QPointF position{};
  if (mouse_area_ != nullptr)
  {
    auto xScale = LvglRenderer::Max_Width / mouse_area_->property("width").toFloat();
    auto yScale = LvglRenderer::Max_Height / mouse_area_->property("height").toFloat();
    position.setX(mouse_area_->property("mouseX").toFloat() * xScale);
    position.setY(mouse_area_->property("mouseY").toFloat() * yScale);
  }
  return position;
}

bool LvglImageProvider::isMousePressed() const noexcept
{
  bool is_pressed = false;
  if (mouse_area_ != nullptr)
  {
    is_pressed = mouse_area_->property("pressedButtons").toInt() != 0;
  }
  return is_pressed;
}

static void mouseRead(lv_indev_drv_t* device, lv_indev_data_t* data)
{
  auto* view        = static_cast<LvglImageProvider*>(device->user_data);
  auto  mouse_point = view->mousePosition();
  data->point.x     = mouse_point.x();
  data->point.y     = mouse_point.y();
  data->state       = view->isMousePressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}
