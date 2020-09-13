// 3rd Party
#include <QtGlobal>

// Local
#include "LvglRenderer.hpp"
#include "LvglImageProvider.hpp"

LvglImageProvider::LvglImageProvider(LvglRenderer& renderer)
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
    , renderer_{ renderer }
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
    *size = { LvglRenderer::Max_Width, LvglRenderer::Max_Height };
  }

  lv_tick_inc(LvglRenderer::Tick_Period_Ms);
  lv_task_handler();

  return renderer_.pixmap().scaled(
    requestedSize.width() > 0 ? requestedSize.width() : LvglRenderer::Max_Width,
    requestedSize.height() > 0 ? requestedSize.height() : LvglRenderer::Max_Height);
}
