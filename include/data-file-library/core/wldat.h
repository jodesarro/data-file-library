/* 
    Data File Library: A set of C functions for handling numeric data files

    File: include/data-file-library/core/wldat.h
    Version: include/data-file-library/version.h
    Author: Jhonas Olivati de Sarro
    Language standards: C99 with guards for C++98 compatibility
    License: include/data-file-library/license.txt

    Description:
        Functions for handling files having the structure of a Wolfram
        Language file format (nested braces).
*/

#ifndef DATA_FILE_LIBRARY_WLDAT_H
#define DATA_FILE_LIBRARY_WLDAT_H

#ifndef DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
#define DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_ static inline
#endif

#ifdef __cplusplus

/* Includes, typedefs and/or macros for C++98 compatibility */

#include <complex> /* For complex numbers */
typedef std::complex<double> tpdcomplex_impl_;

extern "C" {

#else

#include <complex.h> /* For complex numbers */
typedef double complex tpdcomplex_impl_;

#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h> /* For EXIT_FAILURE */
#include <ctype.h>
#include "../impl/wldat_impl_.h"

/*
    Returns the size of the comment of a Wolfram
    Language file format, i.e., the number of characters of the first line of
    the file plus a '\0' char.

    Parameters:
    - wldat_path, path to the file.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
int wldat_get_comment_size(const char *wldat_path) {
    return wldat_get_comment_size_impl_(wldat_path);
}

/*
    Gets the comment of a Wolfram Language file format,
    i.e., the text of the whole first line plus a '\0' char.

    Parameters:
    - wldat_path, path to the file.
    - comment, array of size wldat_get_comment_size(wldat_path) to store
    the text.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void wldat_get_comment(const char *wldat_path, char *comment) {
    wldat_get_comment_impl_(wldat_path, comment);
}

/*
    Returns the number of dimensions of a Wolfram
    Language file format. The number of dimensions must not exceed 128.

    Parameters:
    - wldat_path, path to the file.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
int wldat_get_dimensions(const char *wldat_path) {
    wldat_get_dimensions_impl_(wldat_path);
}

/*
    Gets the size of each dimension of a Wolfram Language file format.

    Parameters:
    - wldat_path, path to the file.
    - sizes, array of size wldat_get_dimensions(wldat_path) to
    sequentially store the size of each dimension. The size of this array must
    not exceed 128.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void wldat_get_sizes(const char *wldat_path, int *sizes) {
    wldat_get_sizes_impl_(wldat_path, sizes);
}

/*
    Imports data of real numbers of a Wolfram Language file format.

    Parameters:
    - wldat_path, path to the data file.
    - data_array, array of size S1*S2*...*SN to store the results, where
    N is the number of dimensions, and for each dimension n,
    where 1 <= n <= N, Sn is its size. Notice that N may be obtained through
    wldat_get_dimensions(wldat_path) and Sn through
    wldat_get_sizes(wldat_path).
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void wldat_import(const char *wldat_path, double *data_array) {
    wldat_import_impl_(wldat_path, data_array);
}

/*
    Imports data of complex numbers of a Wolfram Language file format.

    Parameters:
    - wldat_path, path to the data file.
    - data_array, array of size S1*S2*...*SN to store the results, where
    N is the number of dimensions, and for each dimension n,
    where 1 <= n <= N, Sn is its size. Notice that N may be obtained through
    wldat_get_dimensions(wldat_path) and Sn through
    wldat_get_sizes(wldat_path).
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void wldat_import_cplx(const char *wldat_path,
    tpdcomplex_impl_ *data_array) {

    wldat_import_cplx_impl_(wldat_path, data_array); 
}

/*
    Exports data of real numbers to a Wolfram Language file format.

    Parameters:
    - wldat_path, path to the data file.
    - data_array, array of size S1*S2*...*SN to store the results, where
    N is the number of dimensions, and for each dimension n,
    where 1 <= n <= N, Sn is its size.
    - dimensions, number of the dimensions of the data.
    - sizes, array with the size of each dimension.
    - comment, text to be stored at the very first line of the file.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void wldat_export(const char *wldat_path,
    double *data_array, int dimensions, int *sizes, char *comment) {

    wldat_export_impl_(wldat_path, data_array, dimensions, sizes, comment);
}

/*
    Exports data of complex numbers to a Wolfram Language file format.

    Parameters:
    - wldat_path, path to the data file.
    - data_array, array of size S1*S2*...*SN to store the results, where
    N is the number of dimensions, and for each dimension n,
    where 1 <= n <= N, Sn is its size.
    - dimensions, number of the dimensions of the data.
    - sizes, array with the size of each dimension.
    - comment, text to be stored at the very first line of the file.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void wldat_export_cplx(const char *wldat_path,
    tpdcomplex_impl_ *data_array, int dimensions, int *sizes, char *comment) {

    wldat_export_cplx_impl_(wldat_path, data_array, dimensions, sizes,
        comment);
}

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* DATA_FILE_LIBRARY_WLDAT_H */