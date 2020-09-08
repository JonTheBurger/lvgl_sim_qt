cmake_minimum_required(VERSION 3.14)
project(lvgl_sim_qt LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

add_executable(lvgl_qt_widgets
  src/lvgl_qt_widgets/main.cpp
  src/lvgl_qt_widgets/MainWindow.cpp
  src/lvgl_qt_widgets/MainWindow.hpp
  src/lvgl_qt_widgets/MainWindow.ui
)
target_link_libraries(lvgl_qt_widgets
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    lvgl
)

add_executable(lvgl_qt_quick
  src/lvgl_qt_quick/main.cpp
  src/lvgl_qt_quick/qml.qrc
)
target_link_libraries(lvgl_qt_quick
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Quick
)
target_compile_definitions(lvgl_qt_quick
  PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
