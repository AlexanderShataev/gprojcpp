project(libtreeanalyzer)

include_directories(include)

SET(SOURCES
        treenode.cpp
        regions.cpp
        csvregionparser.cpp
)

add_library(${PROJECT_NAME}
        ${SOURCES}
)

add_library(libs::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

find_package(Boost REQUIRED COMPONENTS system iostreams)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${Boost_LIBRARIES})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories(${Boost_INCLUDE_DIRS})

if(BUILD_TESTING)
    add_subdirectory(tests)
endif ()
