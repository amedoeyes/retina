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
