cmake_minimum_required(VERSION 3.22.1)
project(regionAndCityApp VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(CTest)

add_subdirectory(libs)
add_subdirectory(app)
add_subdirectory(3rdparty/googletest)
