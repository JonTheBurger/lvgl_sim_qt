set(LV_CONF_PATH ${CMAKE_CURRENT_LIST_DIR}/lv_conf.h CACHE STRING "")
add_subdirectory(lvgl)
add_subdirectory(lv_demos)
target_include_directories(lvgl
  PUBLIC
    ${PROJECT_SOURCE_DIR}/external/lvgl/src
)
target_include_directories(lvgl_examples
  PUBLIC
    ${PROJECT_SOURCE_DIR}/external/lvgl/examples
)
target_include_directories(lv_demos
  PUBLIC
    ${PROJECT_SOURCE_DIR}/external/lvgl_demos/examples
)
