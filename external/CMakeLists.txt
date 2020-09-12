file(GLOB_RECURSE lvgl_sources lvgl/*.c)
file(GLOB_RECURSE lvgl_headers lvgl/*.h)
add_library(lvgl
  lv_conf.h
  ${lvgl_sources}
  ${lvgl_headers}
)
target_include_directories(lvgl
  PUBLIC
    .
    lvgl
    lvgl/src
    lvgl/src/lv_core
    lvgl/src/lv_draw
    lvgl/src/lv_font
    lvgl/src/lv_hal
    lvgl/src/lv_misc
    lvgl/src/lv_themes
    lvgl/src/lv_widgets
)

file(GLOB_RECURSE lv_examples_sources lv_examples/*.c)
file(GLOB_RECURSE lv_examples_headers lv_examples/*.h)
add_library(lv_examples
  lv_ex_conf.h
  ${lv_examples_sources}
  ${lv_examples_headers}
)
target_include_directories(lv_examples
  PUBLIC
    .
    lv_examples
    lv_examples/src
    lv_examples/src/lv_demo_benchmark
    lv_examples/src/lv_demo_keyboard_encoder
    lv_examples/src/lv_demo_printer
    lv_examples/src/lv_demo_stress
    lv_examples/src/lv_demo_widgets
    lv_examples/src/lv_ex_get_started
    lv_examples/src/lv_ex_style
    lv_examples/src/lv_ex_widgets
)
target_link_libraries(lv_examples
  PUBLIC
    lvgl
)
