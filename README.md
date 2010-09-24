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

### Options

- `-DCMAKE_INSTALL_PREFIX=<path>` defines the installation prefix to `<path>`.
- `-DBOOSTNUMERICBINDINGS_DIR=<path>` where `<path>` is the installation
   prefix of Boost numeric bindings. This is required is the numeric bindings
   are not installed in a standard prefix[1].


[1] Boost numeric bindings have been merged into Boost uBLAS in Boost
1.41. By consequence, if your Boost version is newer than 1.41, you
should ignore this option.
