cmake_minimum_required(VERSION 3.20)
project(MyQtApp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# ----------------------------
# Qt modules 
# ----------------------------
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Svg SvgWidgets LinguistTools OpenGLWidgets PrintSupport)
qt_standard_project_setup()
# ----------------------------
# Executable
# ----------------------------
qt_add_executable(MyQtApp
   WIN32 main.cpp
)
# ----------------------------
# Resources
# ----------------------------
qt_add_resources(MyQtApp "app_resources"
    PREFIX "/"
    BASE "${CMAKE_SOURCE_DIR}/res"
    FILES "${CMAKE_SOURCE_DIR}/res/logo.svg"
)
# ----------------------------
# Qt linking 
# ----------------------------
target_link_libraries(MyQtApp PRIVATE
    Qt6::Widgets
    Qt6::Gui
    Qt6::Svg
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    Qt6::PrintSupport
)
# ----------------------------
# SDK includes
# ----------------------------
target_include_directories(MyQtApp PRIVATE
    ${CMAKE_SOURCE_DIR}/SDK/Kernel/include
    ${CMAKE_SOURCE_DIR}/SDK/Vision/include
    ${CMAKE_SOURCE_DIR}/SDK/QVision
)
# ----------------------------
# SDK libraries
# ----------------------------
target_link_libraries(MyQtApp PRIVATE
    debug     ${CMAKE_SOURCE_DIR}/SDK/Kernel/debug/c3d.lib
    optimized ${CMAKE_SOURCE_DIR}/SDK/Kernel/release/c3d.lib
    debug     ${CMAKE_SOURCE_DIR}/SDK/Vision/debug/c3dvision.lib
    optimized ${CMAKE_SOURCE_DIR}/SDK/Vision/release/c3dvision.lib
)
file(GLOB QVISION_SOURCES
    ${CMAKE_SOURCE_DIR}/SDK/QVision/*.cpp
)
target_sources(MyQtApp PRIVATE ${QVISION_SOURCES})
# ----------------------------
# Dialog sources
# ----------------------------
file(GLOB_RECURSE DIALOG_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/Dialog/*.cpp
)
target_sources(MyQtApp PRIVATE ${DIALOG_SOURCES})
target_include_directories(MyQtApp PRIVATE
    ${CMAKE_SOURCE_DIR}/src/Dialog
)
file(GLOB_RECURSE SRC_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)
target_sources(MyQtApp PRIVATE ${SRC_SOURCES})
target_include_directories(MyQtApp PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)
file(GLOB_RECURSE WIDGET_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/Widget/*.cpp
)
target_sources(MyQtApp PRIVATE ${WIDGET_SOURCES})
target_include_directories(MyQtApp PRIVATE
    ${CMAKE_SOURCE_DIR}/src/Widget
)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
else()
    add_compile_definitions(RELEASE)
endif()
if(WIN32)
    add_compile_definitions(OS_WINDOWS)
else()
    add_compile_definitions(OS_LINUX)
endif()