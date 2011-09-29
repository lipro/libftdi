METASOURCES = AUTO
INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/ftdipp
LDADD = $(top_builddir)/src/libftdi.la


if HAVE_LIBFTDIPP
examples_libftdipp = find_all_pp
else
examples_libftdipp =
endif


if BUILD_EXAMPLES
all_examples = simple \
	bitbang       \
	bitbang2      \
	bitbang_ft2232 \
	bitbang_cbus \
	find_all \
	serial_test \
	baud_test \
	$(examples_libftdipp)
else
all_examples =
endif
bin_PROGRAMS = $(all_examples)

# Don't install the example files
AM_LDFLAGS = -no-install

simple_SOURCES = simple.c
bitbang_SOURCES = bitbang.c
bitbang2_SOURCES = bitbang2.c
bitbang_ft2232_SOURCES = bitbang_ft2232.c
bitbang_cbus_SOURCES = bitbang_cbus.c
find_all_SOURCES = find_all.c
serial_test_SOURCES = serial_test.c
baud_test_SOURCES = baud_test.c

if HAVE_LIBFTDIPP
find_all_pp_SOURCES = find_all_pp.cpp
find_all_pp_LDADD = $(top_builddir)/ftdipp/libftdipp.la $(LDADD)
endif

EXTRA_DIST = CMakeLists.txt
