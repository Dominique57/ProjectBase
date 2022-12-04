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
target_compile_options(coverage_options
    INTERFACE
        "--coverage"
)
target_link_options(coverage_options
    INTERFACE
        "--coverage"
)


# create SOURCE_LIB static library: user souce library
add_subdirectory(src)

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
