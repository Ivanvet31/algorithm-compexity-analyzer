cmake_minimum_required(VERSION 3.28)
project(ForumPetProject)

set(PROJECT_NAME ForumPetProject)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

set(SOURCES
        main.cpp
)

set(HEADERS
)

include_directories(
        ${PROJECT_SOURCE_DIR}
)

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
