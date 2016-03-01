project(final)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS -lev)

link_directories(/usr/lib)
include_directories(/usr/lib)

file(GLOB SOURCES "*.cpp")

add_executable(final  ${SOURCES})

target_link_libraries(final ev)


#project(final)
#cmake_minimum_required(VERSION 2.8)

#set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -lev")

#include_directories(/usr/include)
#link_directories (/usr/include)

##set (EV_SRC /usr/include/ev.h)
##add_library(libev ${EV_SRC})

#file(GLOB SOURCES "*.cpp")

#set(SOURCE_EXE main.cpp)

#add_executable(final  ${SOURCES})

#project(final)
#cmake_minimum_required(VERSION 2.8)

#include_directories(include)

#file(GLOB SOURCES "src/*.cpp")

#include_directories(/usr/include)

#add_executable(${PROJECT_NAME} ${SOURCES})

#target_link_libraries(libtest ${PROJECT_LINK_LIBS} )




#set (CMAKE_CXX_FLAGS "-lev")
#set (CMAKE_LINK_LIBRARY_FLAG "-lev")

#include_directories(/usr/include)
#link_directories(/usr/include/)

#set(SOURCE main.cpp funct.cpp)
#set(SOURCE_EXE main.cpp)
#set(SOURCE_LIB funct.cpp)

#add_library(funct STATIC ${SOURCE_LIB})
#add_executable(final ${SOURCE_EXE})

#target_link_libraries(final funct)


#set (CMAKE_CXX_FLAGS "-lev -pthread")
#aux_source_directory(. SRC_LIST)
#add_executable(${PROJECT_NAME} ${SRC_LIST})
