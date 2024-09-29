project(app)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/mainwindow.cpp
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        libs::libtreeanalyzer
        Qt5::Widgets
)

