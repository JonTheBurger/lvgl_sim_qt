#ifndef LVGLIMAGEPROVIDER_HPP
#define LVGLIMAGEPROVIDER_HPP

// 3rd Party
#include <QQuickImageProvider>

class LvglContext;
class LvglImageProvider final : public QQuickImageProvider {
  LvglContext& context_;

public:
  LvglImageProvider(LvglContext& context);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize, const QQuickImageProviderOptions& options) override;
#else
  QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize) override;
#endif
};

#endif // LVGLIMAGEPROVIDER_HPP
