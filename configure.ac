#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([find_political_donors], [1.0], [ruslan.mardugalliamov@gmail.com])

AC_LANG(C++)

AC_CONFIG_AUX_DIR([src/build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_CONFIG_MACRO_DIR([src/m4])


dnl this allows us specify individual liking flags for each target
#AM_PROG_CC_C_O 

AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_REQUIRE_AUX_FILE([tap-driver.sh])
AM_PROG_AR
AX_CHECK_COMPILE_FLAG([-std=c++14], [CXXFLAGS="$CXXFLAGS -std=c++14"], AC_MSG_ERROR("g++ does not support c++14")) 
AX_CODE_COVERAGE
 
LT_INIT([disable-shared])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/unittests/Makefile])

AC_OUTPUT


