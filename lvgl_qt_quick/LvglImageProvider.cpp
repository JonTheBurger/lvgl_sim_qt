// 3rd Party
#include <QtGlobal>

// Local
#include "LvglContext.hpp"
#include "LvglImageProvider.hpp"

LvglImageProvider::LvglImageProvider(LvglContext& context)
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
    , context_{ context }
{
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
QPixmap LvglImageProvider::requestPixmap(const QString&, QSize* size, const QSize& requestedSize, const QQuickImageProviderOptions&)
#else
QPixmap LvglImageProvider::requestPixmap(const QString&, QSize* size, const QSize& requestedSize)
#endif
{
  if (size != nullptr)
  {
    *size = { LvglContext::Max_Width, LvglContext::Max_Height };
  }

  lv_tick_inc(LvglContext::Tick_Period_Ms);
  lv_task_handler();

  return context_.pixmap().scaled(
    requestedSize.width() > 0 ? requestedSize.width() : LvglContext::Max_Width,
    requestedSize.height() > 0 ? requestedSize.height() : LvglContext::Max_Height);
}
