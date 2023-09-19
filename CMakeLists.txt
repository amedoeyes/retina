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

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)

fetchcontent_declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

fetchcontent_makeavailable(Catch2)

set(BOOST_INCLUDE_LIBRARIES asio beast)
set(BOOST_ENABLE_CMAKE ON)

fetchcontent_declare(
    Boost
    URL
        https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.7z
)

fetchcontent_makeavailable(Boost)
