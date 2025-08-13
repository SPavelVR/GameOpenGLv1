cmake_minimum_required(VERSION 4.0 FATAL_ERROR)

project(Glad LANGUAGES C CXX)

#add_subdirectory("./lib/containers")

# Создаем библиотеку
add_library(Glad STATIC src/glad.c)
target_include_directories(Glad PUBLIC include)