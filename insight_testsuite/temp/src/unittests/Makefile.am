@CODE_COVERAGE_RULES@
ACLOCAL_AMFLAGS = -I $(top_srcdir)/src/m4

check_PROGRAMS = fec_file_parser_test  
fec_file_parser_test_SOURCES = fec_file_parser_test.cpp
fec_file_parser_test_LDADD = $(top_srcdir)/src/libfec_file_parser.la $(top_srcdir)/src/libdate.la
fec_file_parser_test_LDFLAGS = -lstdc++fs
fec_file_parser_test_LIBS = $(CODE_COVERAGE_LIBS)
fec_file_parser_test_CXXFLAGS = $(CODE_COVERAGE_CXXFLAGS) -I $(top_srcdir)/src -Wall -Werror
fec_file_parser_test_CPPFLAGS = $(CODE_COVERAGE_CPPFLAGS)

check_PROGRAMS += running_median_by_zip_calculator_test  
running_median_by_zip_calculator_test_SOURCES = running_median_by_zip_calculator_test.cpp
running_median_by_zip_calculator_test_LDADD = $(top_srcdir)/src/librunning_median_by_zip_calculator.la $(top_srcdir)/src/libdate.la
running_median_by_zip_calculator_test_LDFLAGS = -lstdc++fs
running_median_by_zip_calculator_test_LIBS = $(CODE_COVERAGE_LIBS)
running_median_by_zip_calculator_test_CXXFLAGS = $(CODE_COVERAGE_CXXFLAGS) -I $(top_srcdir)/src -Wall -Werror
running_median_by_zip_calculator_test_CPPFLAGS = $(CODE_COVERAGE_CPPFLAGS)


check_PROGRAMS += running_median_by_date_calculator_test  
running_median_by_date_calculator_test_SOURCES = running_median_by_date_calculator_test.cpp
running_median_by_date_calculator_test_LDADD = $(top_srcdir)/src/librunning_median_by_date_calculator.la $(top_srcdir)/src/libdate.la
running_median_by_date_calculator_test_LDFLAGS = -lstdc++fs
running_median_by_date_calculator_test_LIBS = $(CODE_COVERAGE_LIBS)
running_median_by_date_calculator_test_CXXFLAGS = $(CODE_COVERAGE_CXXFLAGS) -I $(top_srcdir)/src -Wall -Werror
running_median_by_date_calculator_test_CPPFLAGS = $(CODE_COVERAGE_CPPFLAGS)

TESTS_ENVIRONMENT =


TEST_LOG_COMPILE = $(SHELL)

TESTS = $(check_PROGRAMS)


LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) $(top_srcdir)/src/build-aux/tap-driver.sh
EXTRA_DIST = $(TESTS)

