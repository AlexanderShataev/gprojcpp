project(app)


add_executable(${PROJECT_NAME}
        main.cpp
)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        libs::libtreeanalyzer
        Qt5::Widgets
)

