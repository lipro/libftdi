# Project
project(libftdi)
set(MAJOR_VERSION 0)
set(MINOR_VERSION 20)
set(VERSION_STRING ${MAJOR_VERSION}.${MINOR_VERSION})
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

# CMake
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
   set(CMAKE_BUILD_TYPE     Debug)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "")
set(CMAKE_COLOR_MAKEFILE ON)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

add_definitions(-Wall)
# Debug build
message("-- Build type: ${CMAKE_BUILD_TYPE}")
if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
   add_definitions(-DDEBUG)
endif(${CMAKE_BUILD_TYPE} STREQUAL Debug)

FIND_PACKAGE(USB REQUIRED)
INCLUDE_DIRECTORIES(${LIBUSB_INCLUDE_DIR})

# Set components
set(CPACK_COMPONENTS_ALL sharedlibs staticlibs headers)
set(CPACK_COMPONENT_SHAREDLIBS_DISPLAY_NAME "Shared libraries")
set(CPACK_COMPONENT_STATICLIBS_DISPLAY_NAME "Static libraries")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Headers")

set(CPACK_COMPONENT_SHAREDLIBS_DESCRIPTION
"Shared library for general use.")
set(CPACK_COMPONENT_STATICLIBS_DESCRIPTION
"Static library, good if you want to embed libftdi in your application.")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION
"C/C++ header files.")

set(CPACK_COMPONENT_SHAREDLIBS_GROUP "Development")
set(CPACK_COMPONENT_STATICLIBS_GROUP "Development")
set(CPACK_COMPONENT_HEADERS_GROUP    "Development")

# Create suffix to eventually install in lib64
IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
    SET(LIB_SUFFIX "")
    SET(PACK_ARCH "")
  ELSE(CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(LIB_SUFFIX 64)
    SET(PACK_ARCH .x86_64)
endif(CMAKE_SIZEOF_VOID_P EQUAL 4)

# Package information
set(CPACK_PACKAGE_VERSION              ${VERSION_STRING})
set(CPACK_PACKAGE_CONTACT              "Marek Vavrusa <marek@vavrusa.com>")
set(CPACK_PACKAGE_DESCRIPTION          "libftdi library.")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY  ${CPACK_PACKAGE_DESCRIPTION}
                                       )
# Package settings
if(${UNIX})
  set(CPACK_GENERATOR                    "DEB;RPM")
  set(CPACK_CMAKE_GENERATOR              "Unix Makefiles")
  set(CPACK_PACKAGE_NAME                 ${PROJECT_NAME})
  set(CPACK_PACKAGE_FILE_NAME            ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}${PACK_ARCH})
endif(${UNIX})

if(${WIN32})
  set(CPACK_GENERATOR                    "NSIS")
  set(CPACK_CMAKE_GENERATOR              "MinGW Makefiles")
  set(CPACK_PACKAGE_NAME                 "${PROJECT_NAME}")
  set(CPACK_PACKAGE_VENDOR               "")
  set(CPACK_PACKAGE_INSTALL_DIRECTORY    "libftdi")
  set(CPACK_PACKAGE_FILE_NAME            "${PROJECT_NAME}-${VERSION_STRING}-win32")
  set(CPACK_NSIS_DISPLAY_NAME            "libftdi")
  set(CPACK_NSIS_MODIFY_PATH             "ON")
endif(${WIN32})

set(CPACK_RESOURCE_FILE_LICENSE        ${CMAKE_SOURCE_DIR}/LICENSE)

set(CPACK_SOURCE_GENERATOR             TGZ)
set(CPACK_SOURCE_IGNORE_FILES          "\\\\.git")
set(CPACK_SOURCE_PACKAGE_FILE_NAME     ${CPACK_PACKAGE_FILE_NAME})

# Subdirectories
if(${UNIX})
  set(CPACK_SET_DESTDIR "ON")
endif(${UNIX})

add_subdirectory(src)
add_subdirectory(ftdipp)
add_subdirectory(bindings)
add_subdirectory(examples)
add_subdirectory(packages)



# Documentation

option(DOCUMENTATION "Generate API documentation with Doxygen" ON)

find_package(Doxygen)
if(DOCUMENTATION AND DOXYGEN_FOUND)

   # Set variables
   set(PACKAGE libftdi)
   set(VERSION ${VERSION_STRING})
   set(top_srcdir ${CMAKE_SOURCE_DIR})

   # Find doxy config
   message(STATUS "Doxygen found.")
   set(DOXY_DIR "${CMAKE_SOURCE_DIR}/doc")
   set(DOXY_CONFIG "${DOXY_DIR}/Doxyfile.in")

   # Copy doxy.config.in
   configure_file("${DOXY_CONFIG}" "${CMAKE_BINARY_DIR}/doxy.config")

   # Create doc directory
   add_custom_command(
   OUTPUT ${CMAKE_BINARY_DIR}/doc
   COMMAND rm -rf ${CMAKE_BINARY_DIR}/doc/{html,man}
   COMMAND mkdir -p ${CMAKE_BINARY_DIR}/doc
   DEPENDS ftdi ftdipp
   )

   # Run doxygen
   add_custom_command(
   OUTPUT ${CMAKE_BINARY_DIR}/doc/html/index.html
   COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/doxy.config"
   DEPENDS "${CMAKE_BINARY_DIR}/doxy.config" "${CMAKE_BINARY_DIR}/doc"
   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc
   )

   add_custom_target(docs ALL DEPENDS ${CMAKE_BINARY_DIR}/doc/html/index.html)

   message(STATUS "Generating API documentation with Doxygen")
else(DOCUMENTATION AND DOXYGEN_FOUND)
   message(STATUS "Not generating API documentation")
endif(DOCUMENTATION AND DOXYGEN_FOUND)

# PkgConfig
set(prefix      ${CMAKE_INSTALL_PREFIX})
set(exec_prefix ${CMAKE_INSTALL_PREFIX}/bin)
set(includedir  ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})

if(${UNIX})
   set(libdir      ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})
endif(${UNIX})
if(${WIN32})
   set(libdir      ${CMAKE_INSTALL_PREFIX}/bin)
endif(${WIN32})

configure_file(${CMAKE_SOURCE_DIR}/libftdi.pc.in ${CMAKE_BINARY_DIR}/libftdi.pc @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/libftdipp.pc.in ${CMAKE_BINARY_DIR}/libftdipp.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/libftdi.pc ${CMAKE_BINARY_DIR}/libftdipp.pc
        DESTINATION lib${LIB_SUFFIX}/pkgconfig)

if(${UNIX})
    configure_file(${CMAKE_SOURCE_DIR}/libftdi-config.in ${CMAKE_BINARY_DIR}/libftdi-config @ONLY)
    install(PROGRAMS ${CMAKE_BINARY_DIR}/libftdi-config DESTINATION bin)
endif(${UNIX})

include(CPack)
