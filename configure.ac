
dnl 
dnl configure.ac file for package jrlMathTools 
dnl

AC_INIT([jrlMathTools], [1.0.99], [support@company.com])
AC_PREREQ(2.59)

if test "$CFLAGS$CXXFLAGS" = ""; then
  setdefaultflags=yes
else
  setdefaultflags=no
fi

AM_INIT_AUTOMAKE([no-define])

AC_PROG_INSTALL
AC_PROG_CXX

if test "$setdefaultflags" = "yes"; then
  if test "$GCC" = "yes"; then
    CFLAGS="$CFLAGS -Wall"
    AC_MSG_NOTICE([adding default "-Wall" c flags])
  fi
  if test "$GXX" = "yes"; then
    CXXFLAGS="$CXXFLAGS -Wall"
    AC_MSG_NOTICE([adding default "-Wall" c++ flags])
  fi
fi

AC_OUTPUT(
	jrlMathTools.pc
	Makefile
	include/Makefile
	doc/Makefile
	doc/package.dox
	)
