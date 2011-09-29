# Check
set(FTDI_BUILD_CPP False PARENT_SCOPE)

option(FTDIPP "Build C++ binding library libftdi++" ON)

if (FTDIPP)

    # Includes
    include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR}
                        ${CMAKE_CURRENT_SOURCE_DIR}
                        ${CMAKE_SOURCE_DIR}/src
                        )

    # Targets
    set(cpp_sources   ftdi.cpp)
    set(cpp_headers   ftdi.hpp)

    # Find Boost
    find_package(Boost)
    if(Boost_FOUND)
    set(FTDI_BUILD_CPP True PARENT_SCOPE)
    message(STATUS "Building libftdi++")

    # Targets
    add_library(ftdipp SHARED ${cpp_sources})

    math(EXPR VERSION_FIXUP "${MAJOR_VERSION} + 1")    # Compatiblity with previous releases
    set_target_properties(ftdipp PROPERTIES VERSION ${VERSION_FIXUP}.${MINOR_VERSION}.0 SOVERSION 1)

    # Static library
    add_library(ftdipp-static STATIC ${cpp_sources})
    set_target_properties(ftdipp-static PROPERTIES OUTPUT_NAME "ftdipp")

    # Prevent clobbering each other during the build
    set_target_properties(ftdipp PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(ftdipp-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

    # Dependencies
    target_link_libraries(ftdipp ftdi ${LIBUSB_LIBRARIES} ${BOOST_LIBRARIES})

    # Install
    if(${UNIX})

    install( TARGETS ftdipp
                LIBRARY DESTINATION lib${LIB_SUFFIX}
                COMPONENT sharedlibs
                )

    install( TARGETS ftdipp-static
                ARCHIVE DESTINATION lib${LIB_SUFFIX}
                COMPONENT staticlibs
                )

    install( FILES ${cpp_headers}
                DESTINATION include
                COMPONENT headers
                )

    endif(${UNIX})

    if(${WIN32})

    install( TARGETS ftdipp
                DESTINATION bin
                COMPONENT sharedlibs
                )

    install( TARGETS ftdipp-static
                DESTINATION bin
                COMPONENT staticlibs
                )

    install( FILES ${cpp_headers}
                DESTINATION include
                COMPONENT headers
                )

    endif(${WIN32})

    else(Boost_FOUND)
    message(STATUS "Boost not found, won't build libftdi++")
    endif(Boost_FOUND)

else(FTDIPP)

    message(STATUS "Not building libftdi++")

endif(FTDIPP)

