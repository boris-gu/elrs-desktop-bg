cmake_minimum_required(VERSION 3.10.0)
project(elrs-desktop-bg VERSION 0.1.0 LANGUAGES C)

add_executable(elrs-desktop-bg main.c)

target_include_directories(elrs-desktop-bg PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/lua-5.3.6/include
)
target_link_libraries(elrs-desktop-bg PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/lua-5.3.6/liblua.a
)
