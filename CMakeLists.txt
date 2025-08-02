cmake_minimum_required(VERSION 3.21.0)
project(moketest VERSION 0.1.0 LANGUAGES CXX)

add_library(moketest "")
add_subdirectory(src)

target_link_libraries(moketest PUBLIC moke)
target_include_directories(moketest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(moketest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(testzoo)
