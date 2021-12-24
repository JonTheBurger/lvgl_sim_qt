# lvgl_sim_qt

![Demo](demo.png?raw=true "Demo")

Provides a small example of how to embed an [lvgl](https://lvgl.io/) application in both a Qt Widgets and Qt Quick C++
application. Mouse events are supported, and in widgets, basic keyboard is supported (the keyboard driver is hooked into
an automatically created group). Treating the mousewheel as an encoder is left as an exercise to the reader. Demos that
require `lv_drivers` are not currently supported. 32, 16, 8, and 1-bit color are supported, though most examples do not
work well with 1-bit color.

# Building
This software requires:
- C++ >= 14
- CMake >= 3.10
- Qt >= 5.9 or Qt >= 6.2

```bash
git clone https://github.com/JonTheBurger/lvgl_sim_qt.git --recursive
cd lvgl_sim_qt
cmake -Bbuild -S.
```

Executables will be placed in `build/lvgl_qt_quick` and `build/lvgl_qt_widgets`.

# Modifying
Edits lvgl_sim_qt has made to `lv_conf.h` and `lv_demo_conf.h` can be found by searching for `/** lvgl_sim_qt */`, which
precedes all edits. To change which demo is being run, replace the `lv_demo` function call found in each application's
main function. To change the tick period, modify `LvglRenderer::Tick_Period_Ms`. The default value is `16`. Double
buffering can be disabled by providing `lv_disp_buf_init` with `nullptr` instead of `display_frame2_`.

This project is setup to use `lvgl v8.1.0`. When upgrading, be sure to bump both the `lvgl` and `lv_demos` submodules
to matching versions. At the time of writing, the lvgl repo unstable main branch appears to be absorbing lv_demos.

# Implementation Notes
- If attempting to port code, note that `LvglGraphicsView` is added in Qt Designer using [promote widget](https://doc.qt.io/qt-5/designer-using-custom-widgets.html).
- Qt5 does not support 8-bit 332 color, so a quick and dirty 8-bit color palette is generated in this case.
- Both applications render to a `QImage`, so this common functionality is extracted into `lvgl_qt/LvglRenderer`.
- Forward declarations of classes are used when possible to speed up preprocess time.
- All render callbacks are piped through the Qt event loop, so no additional multithreading considerations should be
  necessary for this example.
- `mouseMoveEvent` only registers movement on a mouse click by default, so a simpler position query is used instead.
- The [Qt official docs](https://doc.qt.io/qt-5/qtquick-bestpractices.html) suggest calling C++ from QML over calling
  QML from C++ for maintainability reasons. We set QML properties from C++ when the values are shared between the Quick
  and Widgets applications, and C++ from QML otherwise.
- Decrease `Tick_Period_Ms` to improve responsiveness.
- Resize is supported, and mouse input coordinates are properly scaled.
- The LVGL CMake targets do not properly include all necessary include directories by default, so they are augmented in
  `external/CMakeLists.txt`.
