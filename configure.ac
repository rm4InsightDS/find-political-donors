#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([find_political_donors], [1.0], [ruslan.mardugalliamov@gmail.com])

AC_LANG(C++)

AC_CONFIG_AUX_DIR([src/build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
#AC_CONFIG_SRCDIR([src/main.cpp])
#AC_CONFIG_SRCDIR([config.h.in])
#AC_CONFIG_HEADERS([config.h])

#AC_CANONICAL_SYSTEM

AC_CONFIG_MACRO_DIR([src/m4])

dnl Initialize automake
#AM_INIT_AUTOMAKE

dnl this allows us specify individual liking flags for each target
#AM_PROG_CC_C_O 

# Checks for programs.
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

 
dnl Initialize Libtool
LT_INIT([disable-shared])


# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
#AC_CHECK_HEADER_STDBOOL
#AC_TYPE_SIZE_T
#AC_TYPE_UINT64_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/unittests/Makefile])
                 
                 



AC_OUTPUT


