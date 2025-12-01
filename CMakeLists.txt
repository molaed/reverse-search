cmake_minimum_required(VERSION 3.15...4.0)

project(reverse_search)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS False) # Use C standard only, not GNU extensions

file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB dsa ${CMAKE_CURRENT_SOURCE_DIR}/dsa/src/*.c)

add_executable(
    reverse_search 
    ${dsa}
    ${src}
)

target_compile_options(reverse_search
    PRIVATE

    -Wall
    -Werror
    -Wextra
    -pedantic
)

if (DEBUG)
    target_compile_options(reverse_search PRIVATE -g -O0 -DDEBUG)
endif()

target_include_directories(
    reverse_search
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
)