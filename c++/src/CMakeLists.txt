# Find libraries

# Add your source files here
add_library(SOURCE_LIB STATIC
    # TODO: add your source file here
    sample.cc sample.hh
)

# add important compile features
target_compile_features(SOURCE_LIB PRIVATE
    cxx_std_17
)

target_compile_options(SOURCE_LIB PRIVATE
    "-Wall" "-Wextra" "-pedantic"
    $<$<CONFIG:Release>:-Werror -Ofast>
    $<$<CONFIG:Debug>:-O0 -g0>
)

# link library to my files (ex: -lm for math utilities)
target_link_libraries(SOURCE_LIB
)

# This is gcc's -I option for simple #include<> directive
target_include_directories(SOURCE_LIB PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
