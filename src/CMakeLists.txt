cmake_minimum_required(VERSION 3.20)
project(French_Numbers)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(dependencies)

add_executable(French_Numbers main.cpp)

set(PROJ_SOURCES french_numbers.cpp french_numbers.h)
add_library(StoreLib ${PROJ_SOURCES})
target_include_directories(StoreLib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(StoreLib PUBLIC ghc_filesystem)

enable_testing()
add_subdirectory(tests)
