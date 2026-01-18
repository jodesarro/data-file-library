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
    Returns the size of the comment from a Wolfram
    Language package source format, i.e., the number of characters of the
    first line of the file plus a '\0' char.

    Parameter:
    - file_path, path to the file.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
int wldat_get_comment_size(const char *file_path) {
    return wldat_get_comment_size_impl_(file_path);
}

/*
    Gets the comment from a Wolfram Language package
    source format, i.e., the text of the whole first line of the file plus
    a '\0' char.

    Parameters:
    - file_path, path to the file.
    - comment, array of size given by wldat_get_comment_size(), to
    output the text.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void wldat_get_comment(const char *file_path, char *comment) {
    wldat_get_comment_impl_(file_path, comment);
}

/*
    Returns the number of dimensions from a Wolfram
    Language package source format.
    The number of dimensions is limited to 128.

    Parameter:
    - file_path, path to the file.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
int wldat_get_dimensions(const char *file_path) {
    wldat_get_dimensions_impl_(file_path);
}

/*
    Gets the size of each dimension from a Wolfram
    Language package source format.

    Parameters:
    - file_path, path to the file.
    - size, array of size given by wldat_get_dimensions(), to
    sequentially output the size of each dimension. The size of this array
    is limited to 128.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void wldat_get_sizes(const char *file_path, int *size) {
    wldat_get_sizes_impl_(file_path, size);
}

/*
    Imports data of real numbers from a Wolfram Language
    package source format, and stores in an one-dimensional
    double-type array following the row-major order.

    Parameters:
    - file_path, path to the data file.
    - data, array of double-type of size S1*S2*...*SN to
    output the values following the row-major order, where N is the number of
    dimensions, and for each dimension n, being 1<=n<=N, Sn is its respective
    size. Notice that N<=128 and may be obtained through
    wldat_get_dimensions(), and Sn through wldat_get_sizes().
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void wldat_import(const char *file_path, double *data) {
    wldat_import_impl_(file_path, data);
}

/*
    Imports data of complex numbers from a Wolfram
    Language package source format, and stores in an one-dimensional
    'double complex'-type array following the row-major order.

    Parameters:
    - file_path, path to the data file.
    - data, array of 'double complex'-type of size S1*S2*...*SN to
    output the values following the row-major order, where N is the number of
    dimensions, and for each dimension n, being 1<=n<=N, Sn is its respective
    size. Notice that N<=128 and may be obtained through
    wldat_get_dimensions(), and Sn through wldat_get_sizes().
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void wldat_import_cplx(const char *file_path,
    tpdcomplex_impl_ *data) {

    wldat_import_cplx_impl_(file_path, data); 
}

/*
    Exports double-type data of an one-dimensional
    double-type array, following the row-major order, to Wolfram Language
    package source format of arbitrary dimension.

    Parameters:
    - file_path, path to the data file.
    - data, array of double-type of size S1*S2*...*SN, containing data
    following the row-major order, where N is the number of dimensions,
    and for each dimension n, being 1<=n<=N, Sn is its respective size.
    - dimensions, number N of the dimensions of the data, limited to 128.
    - size, array of size N containing the size of each dimension.
    - comment, text to be stored at the very first line of the file.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void wldat_export(const char *file_path,
    const double *data, int dimensions, const int *size,
    const char *comment) {

    wldat_export_impl_(file_path, data, dimensions, size, comment);
}

/*
    Exports 'double complex'-type data of an
    one-dimensional 'double complex'-type array, following the row-major
    order, to Wolfram Language package source format of arbitrary dimension.

    Parameters:
    - file_path, path to the data file.
    - data, array of 'double complex'-type of size S1*S2*...*SN,
    containing data following the row-major order, where N is the number of
    dimensions, and for each dimension n, being 1<=n<=N, Sn is its respective
    size.
    - dimensions, number N of the dimensions of the data, limited to 128.
    - size, array of size N containing the size of each dimension.
    - comment, text to be stored at the very first line of the file.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void wldat_export_cplx(const char *file_path,
    const tpdcomplex_impl_ *data, int dimensions, const int *size,
    const char *comment) {

    wldat_export_cplx_impl_(file_path, data, dimensions, size,
        comment);
}

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* DATA_FILE_LIBRARY_WLDAT_H */