cmake_minimum_required(VERSION 3.28)

set(project "utils")
project(${project})

set(CMAKE_CXX_STANDARD 20)

set(${project}_SOURCES
        thread_pool.cpp)

set(${project}_HEADERS
        singleton.h
        thread_pool.h)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_library(${project}
        STATIC
        ${${project}_SOURCE_LIST})
