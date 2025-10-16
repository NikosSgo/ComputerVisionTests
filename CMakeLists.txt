cmake_minimum_required(VERSION 3.16)
project(UniversityAutoTest VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)

if(OpenCV_FOUND)
  message(STATUS "OpenCV version: ${OpenCV_VERSION}")
  message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
  message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

  # Добавляем include директории для компилятора
  include_directories(${OpenCV_INCLUDE_DIRS})
endif()

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
