add_executable(retina_test retina_test.cpp)

target_include_directories(retina_test PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(
    retina_test
    PUBLIC retina Catch2::Catch2WithMain Boost::asio Boost::beast
)

set_target_properties(
    retina_test
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/
)

add_test(NAME retina_test COMMAND retina_test)
