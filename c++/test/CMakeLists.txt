find_package(GTest)

if (GTest_FOUND)

    # gather all *.cc files
    file(GLOB TEST_SRC *.cc)

    # if you need to copy from source to build folder do it here
    # configure_file(SRC DST COPYONLY)

    add_executable(UNIT_TEST ${TEST_SRC})
    target_link_libraries(UNIT_TEST
        PRIVATE
            default_options
            SOURCE_LIB
            GTest::GTest
    )

    add_test(NAME test_unitaire
             COMMAND UNIT_TEST)
endif()
