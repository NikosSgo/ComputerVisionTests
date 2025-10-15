include_directories(${CMAKE_SOURCE_DIR}/include)

# Создаем библиотеку математических операций
add_library(math_operations
    math_operations.cpp
)

# Основное приложение
add_executable(main_app
    main.cpp
)

# Линкуем основное приложение с нашей библиотекой
target_link_libraries(main_app math_operations)
