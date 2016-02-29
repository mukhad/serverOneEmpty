project(final)
cmake_minimum_required(VERSION 2.8)

#add_definitions("-lev")
set (CMAKE_CXX_FLAGS "-lev -pthread")

set(SOURCE main.cpp funct.cpp)
set(SOURCE_EXE main.cpp)		# Установка переменной со списком исходников для исполняемого файла
set(SOURCE_LIB funct.cpp)			# Тоже самое, но для библиотеки

add_library(funct STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем foo

add_executable(final ${SOURCE_EXE})

target_link_libraries(final funct)


#set (CMAKE_CXX_FLAGS "-lev -pthread")
#aux_source_directory(. SRC_LIST)
#add_executable(${PROJECT_NAME} ${SRC_LIST})
