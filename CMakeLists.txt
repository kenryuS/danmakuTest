cmake_minimum_required(VERSION 3.14)
project(danmakuTest)

find_package(raylib 3.0 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES
    src/main.cpp
    src/sprites.cpp
    src/cards.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} raylib)
target_include_directories(${PROJECT_NAME} PUBLIC include/)
