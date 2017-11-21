Cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/zhanchi5/hunter/archive/v0.19.137.tar.gz"
    SHA1 "e99ddb16d3b92b7ea9ac4b526faf9415db1c5c5b"
)

project(demo)

hunter_add_package(stack0.0.5)
find_package(stack0.0.5)

add_executable(demo ${CMAKE_CURRENT_SOURCE_DIR}/sources/demo.cpp)
target_link_libraries(demo stack0.0.5)

install(TARGETS demo RUNTIME DESTINATION bin)
