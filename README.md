# lvgl_sim_qt

![Demo](demo.png?raw=true "Demo")

Provides a small example of how to embed an [lvgl](https://lvgl.io/) application in both a Qt Widgets and Qt Quick C++
application. Mouse events are supported, and in widgets, basic keyboard is supported (but must be manually hooked into a
group). Treating the mousewheel as an encoder is left as an exercise to the reader. Demos that require `lv_drivers`
are not currently supported. 32, 16, 8, and 1-bit color are supported, though most examples do not work well with 1-bit
color.

# Building
This software requires:
- C++ >= 14
- CMake >= 3.10
- Qt >= 5.9

```bash
git clone https://github.com/JonTheBurger/lvgl_sim_qt.git --recursive
cd lvgl_sim_qt
cmake -Bbuild -S.
cmake --build build
```

Executables will be placed in `build/lvgl_qt_quick` and `build/lvgl_qt_widgets`.

# Modifying
Edits lvgl_sim_qt has made to `lv_conf.h` and `lv_ex_conf.h` can be found by searching for `/** lvgl_sim_qt */`, which
precedes all edits. To change which demo is being run, replace the `lv_example` function call found after
`/// lvgl_sim_qt_example` in the `main.cpp` files. To change the tick period, modify `LvglRenderer::Tick_Period_Ms`. The
default value is `16`. Double buffering can be disabled by providing `lv_disp_buf_init` with `nullptr` instead of
`display_frame2_`.

This project is setup to use `lvgl v7.4.0`. When upgrading, be sure to bump both the `lvgl` and `lv_examples` submodules
to matching versions.

# Implementation Notes
- If attempting to port code, note that `LvglGraphicsView` is added in Qt Designer using [promote widget](https://doc.qt.io/qt-5/designer-using-custom-widgets.html).
- Some amount of care has been taken to make this repository Qt6 compatible and lvgl update friendly, but no stable
releases exist at time of writing, so these remain untested.
- Qt5 does not support 8-bit 332 color, so a quick and dirty 8-bit color palette is generated in this case.
- Both applications render to a `QImage`, so this common functionality is extracted into `lvgl_qt/LvglRenderer`.
- Forward declarations of classes are used when possible to speed up preprocess time.
- All render callbacks are piped through the Qt event loop, so no additional multithreading considerations should be
necessary for this example.
- `mouseMoveEvent` only registers movement on a mouse click by default, so a simpler position query is used instead.
- Blindly setting Qt Quick properties from C++ is not a great idea in a production application. In fact, don't use this
as an example of QML best practices.
- Decrease `Tick_Period_Ms` to improve responsiveness.
- Resize is supported, and mouse input coordinates are properly scaled.

# Future Work
- _Maybe_ hack around `lv_drivers` to get Qt based keyboard globally registered.
