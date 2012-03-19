# set the include path found by configure
INCLUDES= -I$(top_srcdir)/src @BOOST_CPPFLAGS@

# the library search path.
lib_LTLIBRARIES = libftdipp.la
include_HEADERS = ftdi.hpp
libftdipp_la_SOURCES = ftdi.cpp

# Note:  If you specify a:b:c as the version in the next line,
#  the library that is made has version (a-c).c.b.  In this
#  example, the version is 2.1.2. (3:2:1)
libftdipp_la_LDFLAGS = -version-info 21:0:20 @BOOST_LDFLAGS@
libftdipp_la_LIBADD = $(top_builddir)/src/libftdi.la

EXTRA_DIST = CMakeLists.txt
