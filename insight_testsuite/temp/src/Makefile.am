bin_PROGRAMS = find_political_donors
find_political_donors_SOURCES = main.cpp

# Linker options find-political-donorslib_LTLIBRARIES = libfec_file_parser.la
find_political_donors_LDFLAGS = -lstdc++fs
find_political_donors_LDADD = \
	librunning_median_by_zip_calculator.la \
	librunning_median_by_date_calculator.la \
	libdate.la \
	libfec_file_parser.la

@CODE_COVERAGE_RULES@
lib_LTLIBRARIES = libfec_file_parser.la
libfec_file_parser_la_SOURCES  = fec_file_parser.cpp
libfec_file_parser_la_LDFLAGS  = $(COVERAGE_LDFLAGS) 
libfec_file_parser_la_LIBS     = $(CODE_COVERAGE_LIBS) -lstdc++fs
libfec_file_parser_la_CXXFLAGS = $(COVERAGE_CXXFLAGS) 
libfec_file_parser_la_CPPFLAGS = $(COVERAGE_CPPFLAGS) 

lib_LTLIBRARIES += libdate.la
libdate_la_SOURCES  = date.cpp
libdate_la_LDFLAGS  = $(COVERAGE_LDFLAGS) 
libdate_la_LIBS     = $(CODE_COVERAGE_LIBS) -lstdc++fs
libdate_la_CXXFLAGS = $(COVERAGE_CXXFLAGS) 
libdate_la_CPPFLAGS = $(COVERAGE_CPPFLAGS) 

lib_LTLIBRARIES += librunning_median_by_zip_calculator.la
librunning_median_by_zip_calculator_la_SOURCES  = running_median_by_zip_calculator.cpp
librunning_median_by_zip_calculator_la_LDFLAGS  = $(COVERAGE_LDFLAGS) 
librunning_median_by_zip_calculator_la_LIBS     = $(CODE_COVERAGE_LIBS) -lstdc++fs
librunning_median_by_zip_calculator_la_CXXFLAGS = $(COVERAGE_CXXFLAGS) 
librunning_median_by_zip_calculator_la_CPPFLAGS = $(COVERAGE_CPPFLAGS) 

lib_LTLIBRARIES += librunning_median_by_date_calculator.la
librunning_median_by_date_calculator_la_SOURCES  = running_median_by_date_calculator.cpp
librunning_median_by_date_calculator_la_LDFLAGS  = $(COVERAGE_LDFLAGS) 
librunning_median_by_date_calculator_la_LIBS     = $(CODE_COVERAGE_LIBS) -lstdc++fs
librunning_median_by_date_calculator_la_CXXFLAGS = $(COVERAGE_CXXFLAGS) 
librunning_median_by_date_calculator_la_CPPFLAGS = $(COVERAGE_CPPFLAGS) 


TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/src/build-aux/tap-driver.sh
TESTS = 
EXTRA_DIST = $(TESTS)



SUBDIRS = . unittests
ACLOCAL_AMFLAGS = -I $(top_srcdir)/src/m4


