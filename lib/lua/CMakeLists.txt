project ( lua C )
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

SET(FILES lapi.c
lauxlib.c
lbaselib.c
lcode.c
lcorolib.c
lctype.c
ldblib.c
ldebug.c
ldo.c
ldump.c
lfunc.c
lgc.c
linit.c
liolib.c
llex.c
lmathlib.c
lmem.c
loadlib.c
lobject.c
lopcodes.c
loslib.c
lparser.c
lstate.c
lstring.c
lstrlib.c
ltable.c
ltablib.c
ltests.c
ltm.c
lua.c
lundump.c
lutf8lib.c
lvm.c
lzio.c
onelua.c)

# Создаем библиотеку
add_library(${PROJECT_NAME} STATIC ${FILES})  # STATIC для статической, SHARED для динамической

# Указываем где искать заголовочные файлы
target_include_directories(${PROJECT_NAME} PUBLIC .)