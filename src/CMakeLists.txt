add_library(retina retina.cpp)

target_include_directories(retina PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(retina PUBLIC Boost::asio Boost::beast)
