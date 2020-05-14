# TODO: add package that are needed ONLY for YOUR source code here
find_package(Boost 1.62 COMPONENTS date_time REQUIRED)


# Add your source files here
add_library(SOURCE_LIB STATIC
    # TODO: add your source file here
)

# add flags
target_compile_features(SOURCE_LIB PRIVATE
    cxx_std_17
    cxx_constexpr
)

# this is less clean and portable: literally copy/paste given option to shell
target_compile_options(SOURCE_LIB PRIVATE
    "-Wall"
    "-Wextra"
    $<$<CONFIG:Release>:-Werror>
)

# link library to my files (ex: -lm for math utilities)
target_link_libraries(SOURCE_LIB
    ${Boost_LIBRARIES}
)

# This is gcc's -I option for simple #include<> directive
# we also want to do it for libraries (better system compatibilities)
target_include_directories(SOURCE_LIB PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDE_DIR}
)
