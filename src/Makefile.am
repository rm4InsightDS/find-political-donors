bin_PROGRAMS = find_political_donors
find_political_donors_SOURCES = main.cpp

# Linker options find-political-donors
find_political_donors_LDFLAGS = -lstdc++fs

@CODE_COVERAGE_RULES@
lib_LTLIBRARIES = libfec_file_parser.la

libfec_file_parser_la_SOURCES  = fec_file_parser.cpp
libfec_file_parser_la_LDFLAGS  = $(COVERAGE_LDFLAGS) 
libfec_file_parser_la_LIBS     = $(CODE_COVERAGE_LIBS) -lstdc++fs
libfec_file_parser_la_CXXFLAGS = $(COVERAGE_CXXFLAGS) 
libfec_file_parser_la_CPPFLAGS = $(COVERAGE_CPPFLAGS) 



TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/src/build-aux/tap-driver.sh
TESTS = 
EXTRA_DIST = $(TESTS)



SUBDIRS = . unittests
ACLOCAL_AMFLAGS = -I $(top_srcdir)/src/m4




