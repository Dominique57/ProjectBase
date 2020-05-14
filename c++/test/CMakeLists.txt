find_library(Gtest)

if (G_test)
    enable_testing()

    # gather all *.cc files
    file(GLOB TEST_SRC *.cc)

    # if you need to copy from source to build folder do it here
    configure_file(information.json information.json COPYONLY)

    ADD_EXECUTABLE(TEST_UNITAIRE ${TEST_SRC})

    TARGET_LINK_LIBRARIES(
        TEST_UNITAIRE
        SOURCE_LIB
        ${CRITERION_LIB}
    )

    add_test(NAME test_unitaire
             COMMAND TEST_UNITAIRE)

else()
    message("Missing criterion lib")
endif()
