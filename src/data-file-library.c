/* 
    Data File Library: A set of C functions for handling numeric data files

    File: src/data-file-library.c
    Version: include/data-file-library/version.h
    Author: Jhonas Olivati de Sarro
    Language standards: C99 with C++ guards
    License: include/data-file-library/license.txt

    Description:
        Wrapper for compiling the include/data-file-library.h library.
*/

/* Overwrite 'static inline' */
#if defined(_WIN32) || defined(_WIN64)
    #ifdef __cplusplus
        #define DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_ __declspec(dllexport) extern "C"
    #else
        #define DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_ __declspec(dllexport)
    #endif
#else
    #ifdef __cplusplus
        #define DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_ extern "C"
    #else
        #define DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
    #endif
#endif

#include "../include/data-file-library.h"