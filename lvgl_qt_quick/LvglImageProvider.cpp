// 3rd Party
#include <QObject>

// Local
#include "LvglImageProvider.hpp"
#include "LvglRenderer.hpp"

static void mouseRead(lv_indev_drv_t* device, lv_indev_data_t* data);
static void keyboardRead(lv_indev_drv_t* device, lv_indev_data_t* data);

LvglImageProvider::LvglImageProvider(LvglRenderer& renderer)
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
    , renderer_{ renderer }
    , mouse_area_{ nullptr }
    , mouse_driver_{}
    , mouse_device_{ nullptr }
{
  lv_indev_drv_init(&keyboard_driver_);
  keyboard_driver_.type      = LV_INDEV_TYPE_KEYPAD;
  keyboard_driver_.user_data = this;
  keyboard_driver_.read_cb   = &keyboardRead;
  keyboard_device_           = lv_indev_drv_register(&keyboard_driver_);

  auto* default_group = lv_group_create();
  lv_group_set_default(default_group);
  lv_indev_set_group(keyboard_device_, default_group);

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

Qt::Key LvglImageProvider::key() const noexcept
{
  return key_;
}

void LvglImageProvider::onKeyEvent(Qt::Key key, bool is_pressed)
{
  if (is_pressed)
  {
    key_ = static_cast<Qt::Key>(key);
  }
  else
  {
    key_ = {};
  }
}

static void mouseRead(lv_indev_drv_t* device, lv_indev_data_t* data)
{
  auto* view        = static_cast<LvglImageProvider*>(device->user_data);
  auto  mouse_point = view->mousePosition();
  data->point.x     = mouse_point.x();
  data->point.y     = mouse_point.y();
  data->state       = view->isMousePressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}

static void keyboardRead(lv_indev_drv_t* device, lv_indev_data_t* data)
{
  auto* view  = static_cast<LvglImageProvider*>(device->user_data);
  data->key   = LvglRenderer::toAscii(view->key());
  data->state = (data->key == 0) ? LV_INDEV_STATE_REL : LV_INDEV_STATE_PR;
}
