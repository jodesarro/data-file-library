# CHANGELOG

## v0.0.2 Feb 05, 2026

- Section '## Other programming languages' erased from the README.md.
- Declaration files deleted.
- Replaced, in the core headers, `DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_` by
the `DATA_FILE_LIBRARY_API_IMPL_` macro.
- Created the file include/data-file-library/impl/api_impl_.h.
- Added, in the core headers, the macros `DATA_FILE_LIBRARY_IMPORTS` and
`DATA_FILE_LIBRARY_EXPORTS_IMPL_`, in order to reuse the main header and the
core headers with compiled files.
- File src/data-file-library.c adapted to the new compiled conventions.
- README.me updated.

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