cmake_minimum_required(VERSION 4.0 FATAL_ERROR)

project(CaveCore VERSION 0.0.1 LANGUAGES C CXX)

#add_definitions(-DGLEW_STATIC)  # Важно для статической линковки!

# Исходные файлы (только .c)
set(Files   window/window.c
            events/events.c
    )

add_library(${PROJECT_NAME} STATIC ${Files})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
message("KURWA ${PROJECT_SOURCE_DIR}")



