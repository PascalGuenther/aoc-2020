cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_STANDARD 11)

project(AdventOfCode2020)

add_library(CompileOptions INTERFACE)

if(MSVC)
    target_compile_options(CompileOptions INTERFACE
        /W4
    )
else()
    target_compile_options(CompileOptions INTERFACE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()
if (CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(CompileOptions INTERFACE
        -Weverything
    )
endif()

function(create_executable execName additionalFile)
    add_executable(${execName} main.c ${additionalFile})
    target_link_libraries(${execName} PUBLIC
        CompileOptions
    )
    target_compile_definitions(${execName} PUBLIC
        ${execName}=1
    )
    target_include_directories(${execName} PUBLIC
        inputs
    )
endfunction()

create_executable(DAY3 03.c)
create_executable(DAY4A 04a.c)
create_executable(DAY4B 04b.c)
create_executable(DAY5 05.c)
create_executable(DAY6 06.c)
