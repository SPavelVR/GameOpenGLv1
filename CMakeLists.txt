cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Project1-HelloWorld VERSION 0.0.0 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}\\bin)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)  # Запретить использование более старых стандартов
set(CMAKE_C_EXTENSIONS OFF)        # Отключить GNU-расширения (для строгой совместимости)


add_definitions(-DGLEW_STATIC)  # Важно для статической линковки!


# Исходные файлы (только .c)
set(Files 
    src/mainCPP.cpp
    )

add_executable(${PROJECT_NAME} ${Files})

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE opengl32.lib)

add_subdirectory(extern/glfw-3.4)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_include_directories(${PROJECT_NAME} PUBLIC extern/glfw-3.4/include)

#подключение библиотеки glad
#add_subdirectory(extern/glad)
#target_link_libraries(${PROJECT_NAME} PUBLIC Glad)

# ПЕРЕМЕННЫЕ ДЛЯ БИБЛИОТЕКИ GLEW
set(GLEW_DIR "${CMAKE_SOURCE_DIR}/extern/glew-2.1.0")
set(GLEW_INCLUDE_DIR "${GLEW_DIR}/include")
set(GLEW_LIBRARY "${GLEW_DIR}/lib/Release/x64/glew32s.lib")

target_include_directories(${PROJECT_NAME} PRIVATE "${GLEW_INCLUDE_DIR}")
target_link_libraries(${PROJECT_NAME} PUBLIC "${GLEW_LIBRARY}")

#file(COPY "scripts/" DESTINATION "${CMAKE_BINARY_DIR}/bin/scripts")