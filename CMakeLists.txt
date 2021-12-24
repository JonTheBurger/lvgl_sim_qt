cmake_minimum_required(VERSION 3.10)
project(lvgl_sim_qt LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  if (CMAKE_C_COMPILER_ID MATCHES GNU)
    add_compile_options(-Wall -Wextra -pedantic)
  endif()
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}
  COMPONENTS
    Quick
    Widgets
  REQUIRED
)

add_subdirectory(external)
add_subdirectory(lvgl_qt)
add_subdirectory(lvgl_qt_quick)
add_subdirectory(lvgl_qt_widgets)
