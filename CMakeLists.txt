project(final)
cmake_minimum_required(VERSION 2.8)

#add_definitions("-lev")
set (CMAKE_CXX_FLAGS "-lev -pthread")

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
