// Standard
#include <memory>

// 3rd Party
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <lv_examples/lv_examples.h>

// Local
#include "LvglRenderer.hpp"
#include "LvglImageProvider.hpp"

int main(int argc, char* argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication       app(argc, argv);
  QQmlApplicationEngine engine;
  LvglRenderer          lvgl;
  auto                  lvgl_image_provider = std::make_unique<LvglImageProvider>(lvgl);

  engine.addImageProvider("LvglImageProvider", lvgl_image_provider.release());  // engine takes ownership

  /// lvgl_sim_qt_example
  lv_demo_benchmark();

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  engine.load(url);
  if (engine.rootObjects().isEmpty())
  {
    return EXIT_FAILURE;
  }

  auto* win = qobject_cast<QQuickWindow*>(engine.rootObjects().value(0));
  if (win != nullptr)
  {
    win->setProperty("width", LvglRenderer::Max_Width);
    win->setProperty("height", LvglRenderer::Max_Height);
    win->setProperty("tick_period_ms", LvglRenderer::Tick_Period_Ms);
  }

  return app.exec();
}
