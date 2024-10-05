project(app)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/waitingspinnerwidget.h
        src/waitingspinnerwidget.cpp
)

add_executable(app
    ${PROJECT_SOURCES}
)

include_directories(libs::libtreeanalyzer)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        libs::libtreeanalyzer
        Qt5::Widgets
)

