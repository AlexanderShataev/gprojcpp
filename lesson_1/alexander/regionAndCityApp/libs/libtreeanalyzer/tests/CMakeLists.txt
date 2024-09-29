project(libtreeanalyzer_test)

add_executable(${PROJECT_NAME}
        main.cpp
        test_csvregionparser.cpp)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        libs::libtreeanalyzer
        gtest_main
)

