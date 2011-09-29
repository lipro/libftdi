# Includes
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR}
                     ${CMAKE_CURRENT_SOURCE_DIR}
                     )

# Targets
set(c_sources     ftdi.c)
set(c_headers     ftdi.h)

add_library(ftdi SHARED ${c_sources})

math(EXPR VERSION_FIXUP "${MAJOR_VERSION} + 1")    # Compatiblity with previous releases
set_target_properties(ftdi PROPERTIES VERSION ${VERSION_FIXUP}.${MINOR_VERSION}.0 SOVERSION 1)

# Static library
add_library(ftdi-static STATIC ${c_sources})
set_target_properties(ftdi-static PROPERTIES OUTPUT_NAME "ftdi")

# Prevent clobbering each other during the build
set_target_properties(ftdi PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(ftdi-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# Dependencies
target_link_libraries(ftdi ${LIBUSB_LIBRARIES})

# Install
if(${UNIX})

   install( TARGETS ftdi
            LIBRARY DESTINATION lib${LIB_SUFFIX}
            COMPONENT sharedlibs
            )

   install( TARGETS ftdi-static
            ARCHIVE DESTINATION lib${LIB_SUFFIX}
            COMPONENT staticlibs
            )

   install( FILES ${c_headers}
            DESTINATION include
            COMPONENT headers
            )

endif(${UNIX})

if(${WIN32})

   install( TARGETS ftdi
            DESTINATION bin
            COMPONENT sharedlibs
            )

   install( TARGETS ftdi-static
            DESTINATION bin
            COMPONENT staticlibs
            )

   install( FILES ${c_headers}
            DESTINATION include
            COMPONENT headers
            )

endif(${WIN32})
