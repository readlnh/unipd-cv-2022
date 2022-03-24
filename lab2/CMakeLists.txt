cmake_minimum_required(VERSION 3.8)

project(lab2)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(includes)

add_executable(${PROJECT_NAME} src/main.cc)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
