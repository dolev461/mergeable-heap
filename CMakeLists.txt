cmake_minimum_required(VERSION 3.0.0)
project(maman14 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(maman14 src/main.cpp src/mergeable_heap.cpp src/runner.cpp)
include_directories(include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
