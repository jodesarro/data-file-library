# CHANGELOG

## v0.0.1 Jan 14, 2026

- Added macro for `static inline` for all core functions. Now
src/data-file-library.c just overwrites such macro.
- Added file src/data-file-library-declarations.c containing a list of all the
functions declarations.
- Inclusion of the header version.h in the include/data-file-library.h file.
- Added some missing `static inline` in inclde/impl/parse_impl_.h file.

## v0.0.0 Jan 14, 2026

- Creation of the library with the first routines for handling .csv, .tsv and
.wl files.