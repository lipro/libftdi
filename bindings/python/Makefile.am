
## Process this file with automake to produce Makefile.in

if HAVE_SWIG
if HAVE_PYTHON
if ENABLE_PYTHON_BINDING

LIBFTDI_INTERFACE =	$(top_srcdir)/src/ftdi.h 
SWIG_INTERFACE =	../ftdi.i

BUILT_SOURCES =		ftdi_wrap.c ftdi.py
CLEANFILES =		ftdi_wrap.c ftdi.py

all-local:	ftdi_wrap.c ftdi.py
	@case "`uname`" in \
	  MINGW*) \
		$(PYTHON) setup.py build --compiler=mingw32 \
	  ;; \
	  *) \
		CPPFLAGS="$(CPPFLAGS)" $(PYTHON) setup.py build \
	  ;; \
	esac;

# python on MinGW/MSYS requires pure Windows style paths
# Using following (cd $dir && pwd -W) hack to get a nearly
# native Windows path, then translating the forward slash
# to a backward slash to make python distutils jolly.
# P.S. the backslash has to be escaped thrice, hence a single
# backslash turns into a sequence of eight (neat, huh?)
#
install-exec-local:
	@case "`uname`" in \
	  MINGW*) \
		NATIVE_WINDOWS_PREFIX="`cd $(DESTDIR)$(prefix) && pwd -W`"; \
		NATIVE_WINDOWS_PREFIX="`echo $$NATIVE_WINDOWS_PREFIX | sed -e 's|/|\\\\\\\\|g'`"; \
		$(PYTHON) setup.py install --prefix="$$NATIVE_WINDOWS_PREFIX" \
	  ;; \
	  *) \
		CPPFLAGS="$(CPPFLAGS)" $(PYTHON) setup.py install --prefix=$(DESTDIR)$(prefix) \
	  ;; \
	esac;

# This rule cleans up stuff installed by Python's setup.py
# Unfortunately, Python's distutils do not provide an uninstall
# command, so we have to make up for it here in uninstall-local
# hook. This might break if distutils' behaviour changes as automake
# has no control over what distutils install command does.
#
uninstall-local:
	rm -rf $(DESTDIR)$(libdir)/python*/site-packages/*ftdi*

clean-local:
	$(PYTHON) setup.py clean --all

ftdi_wrap.c ftdi.py:	$(SWIG_INTERFACE) $(LIBFTDI_INTERFACE)
	$(SWIG) -python -I$(top_srcdir)/src -o ftdi_wrap.c -outdir . $(srcdir)/$(SWIG_INTERFACE)


endif # ENABLE_PYTHON_BINDING
endif # HAVE_PYTHON
endif # HAVE_SWIG
