# dftu
A C++ units and physical quantities library.

Planned features:
* C++ 1998-2011 compatible
* thread-safe
* SI units by default/if unspecified in a quantity
* conversion from imperial e.g. feet
* dimensional analysis
* base dimensions e.g. LENGTH, MASS, TIME
* derived dimensions e.g. LENGTH/TIME
* parsing of quantities
* output of quantities
* ASCII symbols by default; possible future support for unicode with an external library such as icu.
* extensive automated test suite

This library will provide run-time ( as opposed to compile-time like in boost unit ) dimensional analysis for values used in scientific and engineering applications.

It aims to be reasonably efficient and self-contained.

CMake will be used as the build system.
