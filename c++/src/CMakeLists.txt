# Find libraries

# Add your source files here
add_library(SOURCE_LIB STATIC
    # TODO: add your source file here
    sample.cc sample.hh
)

# add important compile features
# link library to my files (ex: -lm for math utilities)
target_link_libraries(SOURCE_LIB
    PRIVATE
        default_options
        coverage_options
)

