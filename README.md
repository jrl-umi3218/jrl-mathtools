jrl-mathtools
=============


This package provides small/fixed-size matrices fast computation.
It is released under LGPL-3. See COPYING.LESSER for licensing information.


Setup
-----

To compile this package, it is recommended to create a separate build
directory:


It is recommended to create a specific directory to install this package.

    mkdir _build
    cd _build
    cmake [options] ..
    make install

### Dependencies

The matrix abstract layer depends on several packages which
have to be available on your machine.

 - Libraries:
   - Boost (>= 1.40)
     Its detection is controled by the `BOOST_ROOT` variable, see next section
     for more information.
   - Lapack library
     Use the generic purpose `CMAKE_CXX_FLAGS` and `CMAKE_EXE_LINKER_FLAGS`
     to insert the flags required for the compiler to find your Lapack library
     if it is installed in a non-standard directory.
 - System tools:
   - CMake (>=2.6)
   - pkg-config
   - usual compilation tools (GCC/G++, make, etc.)

### Options

- `-DCMAKE_INSTALL_PREFIX=<path>` defines the installation prefix to `<path>`.
