include(FetchContent)

set(FETCHCONTENT_QUIET OFF)

fetchcontent_declare(
    Boost
    URL
        https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.7z
        DOWNLOAD_EXTRACT_TIMESTAMP
        TRUE
)

fetchcontent_makeavailable(Boost)

add_library(retina retina.cpp)

target_include_directories(retina PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(retina PUBLIC Boost::asio Boost::beast)
