// 3rd Party
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>

// Local
#include "LvglGraphicsView.hpp"

static bool     keyboardRead(lv_indev_drv_t* device, lv_indev_data_t* data);
static uint32_t toAscii(Qt::Key key);
static bool     mouseRead(lv_indev_drv_t* device, lv_indev_data_t* data);

LvglGraphicsView::LvglGraphicsView(QWidget* parent)
    : LvglGraphicsView(nullptr, parent)
{
}

LvglGraphicsView::LvglGraphicsView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
    , renderer_()
    , keyboard_driver_{}
    , mouse_driver_{}
    , keyboard_device_{ nullptr }
    , mouse_device_{ nullptr }
    , key_{}
    , is_mouse_pressed_{ false }
{
  lv_indev_drv_init(&keyboard_driver_);
  keyboard_driver_.type      = LV_INDEV_TYPE_KEYPAD;
  keyboard_driver_.user_data = this;
  keyboard_driver_.read_cb   = &keyboardRead;
  keyboard_device_           = lv_indev_drv_register(&keyboard_driver_);

  lv_indev_drv_init(&mouse_driver_);
  mouse_driver_.type      = LV_INDEV_TYPE_POINTER;
  mouse_driver_.user_data = this;
  mouse_driver_.read_cb   = &mouseRead;
  mouse_device_           = lv_indev_drv_register(&mouse_driver_);
}

void LvglGraphicsView::tick()
{
  lv_tick_inc(LvglRenderer::Tick_Period_Ms);
  lv_task_handler();

  QGraphicsScene* scene = this->scene();
  scene->clear();
  const auto* item = scene->addPixmap(renderer_.pixmap());
  fitInView(item);
}

lv_indev_t* LvglGraphicsView::keyboardDevice()
{
  return keyboard_device_;
}

Qt::Key LvglGraphicsView::key() const noexcept
{
  return key_;
}

QPointF LvglGraphicsView::mousePosition() const
{
  return mapToScene(mapFromGlobal(QCursor::pos()));
}

bool LvglGraphicsView::isMousePressed() const noexcept
{
  return is_mouse_pressed_;
}

void LvglGraphicsView::keyPressEvent(QKeyEvent* event)
{
  key_ = static_cast<Qt::Key>(event->key());
  QGraphicsView::keyPressEvent(event);
}

void LvglGraphicsView::keyReleaseEvent(QKeyEvent* event)
{
  key_ = {};
  QGraphicsView::keyReleaseEvent(event);
}

void LvglGraphicsView::mousePressEvent(QMouseEvent* event)
{
  is_mouse_pressed_ = true;
  QGraphicsView::mousePressEvent(event);
}

void LvglGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
  is_mouse_pressed_ = false;
  QGraphicsView::mouseReleaseEvent(event);
}

static bool keyboardRead(lv_indev_drv_t* device, lv_indev_data_t* data)
{
  auto* view  = static_cast<LvglGraphicsView*>(device->user_data);
  data->key   = toAscii(view->key());
  data->state = (data->key == 0) ? LV_INDEV_STATE_REL : LV_INDEV_STATE_PR;
  return false;
}

static uint32_t toAscii(Qt::Key key)
{
  uint32_t ascii = 0;
  switch (key)
  {
    case Qt::Key_Up:
      ascii = LV_KEY_UP;
    case Qt::Key_Down:
      ascii = LV_KEY_DOWN;
    case Qt::Key_Right:
      ascii = LV_KEY_RIGHT;
    case Qt::Key_Left:
      ascii = LV_KEY_LEFT;
    case Qt::Key_Escape:
      ascii = LV_KEY_ESC;
    case Qt::Key_Delete:
      ascii = LV_KEY_DEL;
    case Qt::Key_Backspace:
      ascii = LV_KEY_BACKSPACE;
    case Qt::Key_Enter:
      ascii = LV_KEY_ENTER;
    case Qt::Key_Tab:
      ascii = LV_KEY_NEXT;
    case Qt::Key_Home:
      ascii = LV_KEY_HOME;
    case Qt::Key_End:
      ascii = (LV_KEY_END);  // lack of parens breaks clang-format for some reason...
    default:
      ascii = key;
      break;
  }
  return key;
}

static bool mouseRead(lv_indev_drv_t* device, lv_indev_data_t* data)
{
  auto* view        = static_cast<LvglGraphicsView*>(device->user_data);
  auto  mouse_point = view->mousePosition();
  data->point.x     = mouse_point.x();
  data->point.y     = mouse_point.y();
  data->state       = view->isMousePressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
  return false;
}
