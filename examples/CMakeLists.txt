option(EXAMPLES "Build example programs" ON)

if (EXAMPLES)
    # Includes
    include( ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_BINARY_DIR}
            )

    message(STATUS "Building example programs.")

    # Source includes
    include_directories(BEFORE ${CMAKE_SOURCE_DIR}/src)

    # Targets
    add_executable(simple simple.c)
    add_executable(bitbang bitbang.c)
    add_executable(bitbang2 bitbang2.c)
    add_executable(bitbang_cbus bitbang_cbus.c)
    add_executable(bitbang_ft2232 bitbang_ft2232.c)
    add_executable(find_all find_all.c)
    add_executable(serial_test serial_test.c)
    add_executable(baud_test baud_test.c)

    # Linkage
    target_link_libraries(simple ftdi)
    target_link_libraries(bitbang ftdi)
    target_link_libraries(bitbang2 ftdi)
    target_link_libraries(bitbang_cbus ftdi)
    target_link_libraries(bitbang_ft2232 ftdi)
    target_link_libraries(find_all ftdi)
    target_link_libraries(serial_test ftdi)
    target_link_libraries(baud_test ftdi)

    # libftdi++ examples
    if(FTDI_BUILD_CPP)
        message(STATUS "Building libftdi++ examples.")
        include_directories(${CMAKE_SOURCE_DIR}/ftdipp)

        # Targest
        add_executable(find_all_pp find_all_pp.cpp)

        # Linkage
        target_link_libraries(find_all_pp ftdipp)
    endif(FTDI_BUILD_CPP)
else(EXAMPLES)
    message(STATUS "Not building example programs.")
endif(EXAMPLES)
