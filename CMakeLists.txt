cmake_minimum_required(VERSION 3.18)
project(Automated_Video_Editing C CXX)
SET(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/FFmpeg)

list(APPEND SOURCES
    src/main.cpp
)

list(APPEND HEADERS
    lib/OutputContext.h
)

add_executable(video_editor ${SOURCES} ${HEADERS})
target_link_libraries(video_editor FFmpeg)