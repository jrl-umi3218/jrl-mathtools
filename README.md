jrl-mathtools
=============

[![Build Status](https://travis-ci.org/jrl-umi3218/jrl-mathtools.png)](https://travis-ci.org/jrl-umi3218/jrl-mathtools)
[![Coverage Status](https://coveralls.io/repos/jrl-umi3218/jrl-mathtools/badge.png?branch=master)](https://coveralls.io/r/jrl-umi3218/jrl-mathtools?branch=master)

This package provides small/fixed-size matrices fast computation. It
is released under [LGPL-3](COPYING.LESSER).


**Warning:** this repository contains [Git
submodules][git-submodules]. Please clone this repository using the
`git clone --recursive` command. If you already have cloned the
repository, you can run `git submodule init && git submodule update`
to retrieve the submodules.


[git-submodules]: http://git-scm.com/book/en/Git-Tools-Submodules

Documentation
-------------

To get started with this library, please read the [online Doxygen
documentation][doxygen-documentation].

It can also be generated locally by running the `make doc`
command. After the package is installed, the documentation will be
located in the `$prefix/share/doc/jrl-mathtools` directoy where
`$prefix` is your installation prefix (`/usr/local` by default).

[doxygen-documentation]: http://jrl-umi3218.github.io/jrl-mathtools/doxygen/HEAD/


Compilation
-----------

To compile this package, it is recommended to create a separate build
directory:

```shell
    mkdir _build
    cd _build
    cmake [options] ..
    make install
```

### Dependencies

The matrix abstract layer depends on several packages which
have to be available on your machine.

 - Libraries:
   - [Boost][boost-website] (>= 1.40)
     Its detection is controled by the `BOOST_ROOT` variable, see next section
     for more information.
   - [Lapack][lapack-website] library
     Use the generic purpose `CMAKE_CXX_FLAGS` and `CMAKE_EXE_LINKER_FLAGS`
     to insert the flags required for the compiler to find your Lapack library
     if it is installed in a non-standard directory.
 - System tools:
   - [CMake][cmake-website] (>=2.6)
   - [pkg-config][pkg-config-website]
   - usual compilation tools (GCC/G++, make, etc.)

[boost-website]: http://www.boost.org/
[lapack-website]: http://www.netlib.org/lapack/
[cmake-website]: http://www.cmake.org/
[pkg-config-website]: http://www.freedesktop.org/wiki/Software/pkg-config/

### Options

- `-DCMAKE_INSTALL_PREFIX=<path>` defines the installation prefix to `<path>`.


Credits
-------

This package authors are credited in the [AUTHORS](AUTHORS) file.
