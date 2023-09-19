cmake_minimum_required(VERSION 3.20)
project(retina LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

