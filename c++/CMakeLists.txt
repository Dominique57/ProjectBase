cmake_minimum_required(VERSION 3.8)

project(MyProject
    VERSION 1.0.0
    DESCRIPTION "First project of 2022 YAKA recruitement phase"
    LANGUAGES CXX
)

set(CMAKE_BUILD_TYPE Debug)

# create SOURCE_LIB static library: user souce library
add_subdirectory(src)

# add test folder
add_subdirectory(test)

# final binary output
add_executable(recruitement_1 src/main.cc)
target_link_libraries(recruitement_1 LINK_PUBLIC SOURCE_LIB)
