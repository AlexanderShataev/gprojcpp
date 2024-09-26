project(libtreeanalyzer_test)


add_executable(${PROJECT_NAME}
        main.cpp
        test_csvregionparser.cpp)

find_package(Boost REQUIRED COMPONENTS system iostreams)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        libs::libtreeanalyzer
        ${Boost_LIBRARIES}
        gtest_main
)
#target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
include_directories(../../../3rdparty/googletest/googletest/include/)
