cmake_minimum_required(VERSION 3.28)

set(project "translator")
project(${project})

set(CMAKE_CXX_STANDARD 23)

set(${project}_SOURCES
        c_types.cpp
        types.cpp
        translation.cpp
)

set(${project}_HEADERS
        types/types.h
        types/c_types.h
        constructions.h
        basic.h
        translation.h
)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_library(${project}
        STATIC
        ${${project}_SOURCE_LIST})
