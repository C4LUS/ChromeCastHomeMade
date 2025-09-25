cmake_minimum_required(VERSION 3.28.3)
project(ChromeCastHomeMade)

set(HEADER_FILES ${CMAKE_SOURCE_DIR}/core/core.h)

add_subdirectory(core)
add_subdirectory(gui)
