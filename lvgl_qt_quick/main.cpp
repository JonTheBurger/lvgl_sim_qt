// Standard
#include <memory>

// 3rd Party
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <lv_demos.h>
#include <lv_examples.h>

// Local
#include "LvglImageProvider.hpp"
#include "LvglRenderer.hpp"

int main(int argc, char* argv[])
{
  // Property deprecated in Qt 6; has no effect.
#if QT_VERSION_MAJOR < 6
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
  QGuiApplication       app(argc, argv);
  QQmlApplicationEngine engine;
  auto                  lvgl                = std::make_unique<LvglRenderer>();
  auto*                 lvgl_image_provider = new LvglImageProvider(*lvgl);
  engine.addImageProvider(QStringLiteral("LvglImageProvider"), lvgl_image_provider);  // engine takes ownership

  /// Uncomment one of the following for a demo
  lv_demo_widgets();
  // lv_demo_stress();
  // lv_demo_benchmark();
  // lv_demo_music();

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  // Set "backend" property in QML so "LvglImageProvider::onKeyEvent" can be invoked.
  engine.rootContext()->setContextProperty("backend", lvgl_image_provider);
  engine.load(url);
  auto* window = qobject_cast<QQuickWindow*>(engine.rootObjects().value(0, nullptr));
  if (window == nullptr)
  {
    return EXIT_FAILURE;
  }
  window->setProperty("width", QVariant::fromValue(LvglRenderer::Max_Width));
  window->setProperty("height", QVariant::fromValue(LvglRenderer::Max_Height));

  auto* timer = window->findChild<QObject*>(QStringLiteral("timer"));
  timer->setProperty("interval", LvglRenderer::Tick_Period_Ms);

  lvgl_image_provider->setMouseArea(window->findChild<QObject*>(QStringLiteral("mouseArea")));

  return app.exec();
}
