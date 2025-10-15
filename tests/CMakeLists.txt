find_package(GTest REQUIRED)

add_executable(run_tests
    test_main.cpp
    test_math.cpp
)

# Линкуем тесты с нашей библиотекой и GTest
target_link_libraries(run_tests
    math_operations
    GTest::gtest
    GTest::gtest_main
)

target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

gtest_discover_tests(run_tests)
