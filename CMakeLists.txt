cmake_minimum_required(VERSION 4.4.0)

project(clap)

option(CLAP_BUILD_EXAMPLES "Build examples" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(clap
    src/Builder/Command.cpp
    src/Lexer/Lexer.cpp
    src/Parser/Parser.cpp
    src/Parser/ArgMatcher.cpp
)

target_include_directories(clap PUBLIC include)

if(CMAKE_BUILD_TYPE EQUAL Debug)
    target_compile_definitions(clap CLAP_CONFIG_DEBUG)
endif()

if(CLAP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()