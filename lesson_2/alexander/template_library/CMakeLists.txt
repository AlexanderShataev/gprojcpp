cmake_minimum_required(VERSION 3.14)

project(template_library LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(template_library SHARED
  src/make_string.h
)

target_link_libraries(template_library PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_compile_definitions(template_library PRIVATE TEMPLATE_LIBRARY_LIBRARY)

add_executable(MAKESTRING_TEST test/test_make_string.cpp)
