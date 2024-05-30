cmake_minimum_required(VERSION 3.28)
project(algorithm-compexity-analyzer)

include(FetchContent)
set(PROJECT_NAME algorithm-compexity-analyzer)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif (CCACHE_FOUND)

set(SOURCES
        main.cpp
)

set(HEADERS
)

include_directories(
        ${PROJECT_SOURCE_DIR}
)

FetchContent_Declare(
        tomlplusplus
        GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
        GIT_TAG v3.4.0
)

FetchContent_Declare(
        ncurses
        URL https://ftp.gnu.org/pub/gnu/ncurses/ncurses-6.3.tar.gz
)

FetchContent_Declare(
        muparser
        GIT_REPOSITORY https://github.com/beltoforion/muparser.git
)

FetchContent_MakeAvailable(tomlplusplus)
FetchContent_MakeAvailable(ncurses)
FetchContent_MakeAvailable(muparser)

add_subdirectory(utils)
add_subdirectory(translator)

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} utils)
target_link_libraries(${PROJECT_NAME} parsing)
target_link_libraries(${PROJECT_NAME} translator)

target_link_libraries(${PROJECT_NAME} tomlplusplus::tomlplusplus)
target_link_libraries(${PROJECT_NAME} ncurses)
target_link_libraries(${PROJECT_NAME} muparser)
