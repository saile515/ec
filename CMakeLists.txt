cmake_minimum_required(VERSION 3.30)

project(ec LANGUAGES C)

set(SOURCES 
    src/filesystem.c
    src/string.c
    src/vector.c
    src/math/matrix4.c
)

set(HEADERS
    include/ec/filesystem.h
    include/ec/string.h
    include/ec/vector.h
)

add_library(ec SHARED ${SOURCES} ${HEADERS})
target_include_directories(ec PUBLIC include)
