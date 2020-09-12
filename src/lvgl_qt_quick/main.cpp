#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <memory>

#include "LvglImageProvider.hpp"

void create_demo();

int main(int argc, char* argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication       app(argc, argv);
  QQmlApplicationEngine engine;
  QQmlContext           context(engine.rootContext());

  engine.addImageProvider("LvglImageProvider", new LvglImageProvider());  // engine takes ownership
  create_demo();

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  engine.load(url);
  if (engine.rootObjects().isEmpty())
  {
    return EXIT_FAILURE;
  }

  auto* win = qobject_cast<QQuickWindow*>(engine.rootObjects().value(0));
  if (win == nullptr)
  {
    return EXIT_FAILURE;
  }
  win->setProperty("width", LV_HOR_RES_MAX);
  win->setProperty("height", LV_VER_RES_MAX);
  win->setProperty("tick_period_ms", LvglImageProvider::tick_period_ms);

  return app.exec();
}

void create_demo()
{
  static lv_obj_t* label1 = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK); /*Break the long lines*/
  lv_label_set_recolor(label1, true);                  /*Enable re-coloring by commands in the text*/
  lv_label_set_align(label1, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
  lv_label_set_text(label1, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label "
                            "and  wrap long text automatically.");
  lv_obj_set_width(label1, 150);
  lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, -30);

  static lv_obj_t* label2 = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(label2, LV_LABEL_LONG_SROLL_CIRC); /*Circular scroll*/
  lv_obj_set_width(label2, 150);
  lv_label_set_text(label2, "It is a circularly scrolling text. ");
  lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 30);
}
