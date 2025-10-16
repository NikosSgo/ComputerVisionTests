# Найти пакет GTest
find_package(GTest REQUIRED)

# Создаем папку для тестовых данных в build/tests/data
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)

# Исполняемый файл тестов
add_executable(run_tests
    test_main.cpp
    labs/test_lab_1.cpp
)

# Копируем тестовые данные из tests/data/ в build/tests/data/
file(GLOB TEST_DATA_FILES ${CMAKE_SOURCE_DIR}/tests/data/*)
foreach(test_file ${TEST_DATA_FILES})
  get_filename_component(filename ${test_file} NAME)
  add_custom_command(
        TARGET run_tests PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/tests/data/${filename}
            ${CMAKE_CURRENT_BINARY_DIR}/data/${filename}
        COMMENT "Copying test data: ${filename}"
    )
endforeach()

# Связываем с GTest и основной библиотекой
target_link_libraries(run_tests
    GTest::gtest
    GTest::gtest_main
    lab_1
)

# Добавляем include директории
target_include_directories(run_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)

# Добавляем тест в CTest
add_test(NAME Lab1Tests COMMAND run_tests)
