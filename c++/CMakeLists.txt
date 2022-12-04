cmake_minimum_required(VERSION 3.8)

project(MyProject
    VERSION 1.0.0
    DESCRIPTION "Description"
    LANGUAGES CXX
)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE Release)
endif()

# Custom cmake file folder location
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/res/cmake/")

# Enable "coverage" target
option(CODE_COVERAGE "Should code coverage be enabled (debug only)" ON)
if (NOT UNIX OR NOT CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CODE_COVERAGE OFF)
endif()

# Enable "static-check" target
option(CODE_CHECKS "Should static analysis (clang-tidy) be enabled" ON)
if (NOT UNIX)
    set(CODE_CHECKS OFF)
endif()
if (CODE_CHECKS)
    SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()


# Create re-usable config libraries
## Default compilation options
add_library(default_options INTERFACE)
target_include_directories(default_options
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_compile_features(default_options
    INTERFACE
        cxx_std_17
)
target_compile_options(default_options
    INTERFACE
        "-Wall" "-Wextra" "-pedantic"
        $<$<CONFIG:Release>:-Werror -Ofast>
        $<$<CONFIG:Debug>:-O0 -ggdb>
)

## Code coverage options
add_library(coverage_options INTERFACE)
if (CODE_COVERAGE)
    include(CodeCoverage)
    target_compile_options(coverage_options
        INTERFACE
            "--coverage"
    )
    target_link_options(coverage_options
        INTERFACE
            "--coverage"
    )
endif()


# create SOURCE_LIB static library: user souce library
add_subdirectory(src)

if (CODE_CHECKS)
    find_program(CLANG_TIDY
        NAMES
            clang-tidy
    )
    find_program(RUN_CLANG_TIDY
        NAMES
            run-clang-tidy
    )
    add_custom_target(static-check
        COMMAND ${RUN_CLANG_TIDY} -quiet -p ${CMAKE_BINARY_DIR}
    )
endif()

# add test folder
enable_testing()
add_subdirectory(test)

# final binary output
find_package(Boost COMPONENTS program_options REQUIRED)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(Boost_USE_STATIC_LIBS ON)
endif()

add_executable(${PROJECT_NAME} src/main.cc)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${Boost_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
    ${Boost_LIBRARIES}
    default_options
    SOURCE_LIB
)
