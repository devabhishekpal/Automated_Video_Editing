cmake_minimum_required(VERSION 3.18)
project(Automated_Video_Editing C CXX)
SET(CMAKE_CXX_STANDARD 14)

list(APPEND SOURCES
    src/main.cpp
)

add_executable(video_editor ${SOURCES})
target_link_libraries(video_editor )