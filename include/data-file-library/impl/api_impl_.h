/*
  Data File Library: A set of C functions for handling numeric data files

  Repository: <https://github.com/jodesarro/data-file-library>
  License: Refer to the LICENSE file in the Repository
  Language standard: C99

  Description: Define the API with macros for C++, for compilation, and for
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

#if defined(DATA_FILE_LIBRARY_EXPORTS_IMPL_) ||                                \
    defined(DATA_FILE_LIBRARY_IMPORTS)
#define DATA_FILE_LIBRARY_API_IMPL_                                            \
  DATA_FILE_LIBRARY_CPP_IMPL_ DATA_FILE_LIBRARY_VISIBILITY_IMPL_
#else
#define DATA_FILE_LIBRARY_API_IMPL_ DATA_FILE_LIBRARY_VISIBILITY_IMPL_
#endif

#endif /* DATA_FILE_LIBRARY_API_IMPL_H */