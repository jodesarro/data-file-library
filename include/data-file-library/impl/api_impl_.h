/*
  Data File Library: A set of C functions for handling numeric data files

  File: include/data-file-library/impl/api_impl_.h
  Language standards: C99
  License: include/data-file-library/license.txt
  Repository: <https://github.com/jodesarro/data-file-library>

  Description: Define the API with macros for C++, and for compilation, and for
  header-only or compiled library usage.
*/

#ifndef DATA_FILE_LIBRARY_API_IMPL_H
#define DATA_FILE_LIBRARY_API_IMPL_H

#ifdef DATA_FILE_LIBRARY_EXPORTS_IMPL_
#if defined(_WIN32) || defined(_WIN64)
#define DATA_FILE_LIBRARY_VISIBILITY_IMPL_ __declspec(dllexport)
#else
#define DATA_FILE_LIBRARY_VISIBILITY_IMPL_                                     \
  __attribute__((visibility("default")))
#endif
#elif defined(DATA_FILE_LIBRARY_IMPORTS)
#if defined(_WIN32) || defined(_WIN64)
#define DATA_FILE_LIBRARY_VISIBILITY_IMPL_ __declspec(dllimport)
#else
#define DATA_FILE_LIBRARY_VISIBILITY_IMPL_
#endif
#else
#define DATA_FILE_LIBRARY_VISIBILITY_IMPL_ static inline
#endif

#ifdef __cplusplus
#define DATA_FILE_LIBRARY_CPP_IMPL_ extern "C"
#else
#define DATA_FILE_LIBRARY_CPP_IMPL_
#endif

#define DATA_FILE_LIBRARY_API_IMPL_                                            \
  DATA_FILE_LIBRARY_VISIBILITY_IMPL_ DATA_FILE_LIBRARY_CPP_IMPL_

#endif /* DATA_FILE_LIBRARY_API_IMPL_H */