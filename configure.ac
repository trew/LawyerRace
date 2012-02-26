#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([Lawyer Race], [0.0.001])
AC_CONFIG_AUX_DIR([m4])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE(1.10 no-define)

# Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL

# Checks for libraries.
BOOST_REQUIRE
AC_CHECK_LIB([SDL], [exit])
AC_CHECK_LIB([SDL_image], [exit])
AC_CHECK_LIB([SDL_ttf], [exit])
AC_CHECK_LIB([boost_program_options], [exit])

# Checks for header files.
AC_PATH_X
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([fenv.h float.h inttypes.h limits.h malloc.h memory.h stddef.h stdint.h stdlib.h string.h strings.h unistd.h wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_CHECK_FUNCS([fesetround floor getcwd modf pow select sqrt])

AC_CONFIG_FILES([Makefile src/Makefile])

AC_OUTPUT
