add_library(lab_1 labs/lab_1.cpp)

target_link_libraries(lab_1 ${OpenCV_LIBS})
target_include_directories(lab_1 PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

# main application
add_executable(main_app main.cpp)
target_link_libraries(main_app lab_1)
