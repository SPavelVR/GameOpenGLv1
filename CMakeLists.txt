cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(TheCave VERSION 0.0.1 LANGUAGES C CXX)

set(VCPKG_CRT_LINKAGE static)
set(VCPKG_LIBRARY_LINKAGE static)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}\\bin)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)  # Запретить использование более старых стандартов
set(CMAKE_C_EXTENSIONS OFF)        # Отключить GNU-расширения (для строгой совместимости)

#add_definitions(-DGLEW_STATIC)  # Важно для статической линковки!

# Исходные файлы (только .c)
set(Files 
    src/main.c
    src/window/window.c
    src/window/events.c
    src/graphics/shader.c
    src/graphics/texture.c
    src/loadsys/loadshaders.c
    src/loadsys/loadTextures.c
    )

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(PNG REQUIRED)
find_package(GLEW REQUIRED)
find_package(Lua REQUIRED)
    
add_executable(${PROJECT_NAME} ${Files})

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${GLEW_INCLUDE_DIRS}
    ${LUA_INCLUDE_DIR}
    # Другие пути...
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    opengl32
    glfw
    GLEW::GLEW
    PNG::PNG
    ${LUA_LIBRARIES}
)

add_subdirectory(lib/containers)
target_link_libraries(${PROJECT_NAME} PUBLIC containers)

#file(COPY "extern/glew/" DESTINATION "${CMAKE_BINARY_DIR}/bin")

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    file(COPY "res/" DESTINATION "${CMAKE_BINARY_DIR}/bin/")
    message(STATUS "Файлы шейдеров скопированы в ${CMAKE_BINARY_DIR}/bin")
else()
    message(STATUS "Debug mode - копирование пропущено")
endif()
