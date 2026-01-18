/* 
    Data File Library: A set of C functions for handling numeric data files

    File: include/data-file-library/core/csvdat.h
    Version: include/data-file-library/version.h
    Author: Jhonas Olivati de Sarro
    Language standards: C99 with guards for C++98 compatibility
    License: include/data-file-library/license.txt

    Description:
        Functions for handling files having a structure in which lines are
        separated by line break and columns are separated by comma.
*/

#ifndef DATA_FILE_LIBRARY_CSVDAT_H
#define DATA_FILE_LIBRARY_CSVDAT_H

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

#include "../impl/sepdat_impl_.h"

/*
    Gets the size in each dimension (number of rows and columns) from a
    Comma-Separated Values data file.

    Parameters:
    - file_path, path to the file.
    - &rows, to output the number of rows.
    - &columns, to output the number of columns.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void csvdat_get_sizes(const char *file_path, int *rows,
    int *columns) {
    
    sepdat_get_sizes_impl_(file_path, rows, columns, ',');
}

/*
    Imports double-type data from a Comma-Separated Values data file
    and stores in an
    one-dimensional double-type array following the row-major order.
    The values may also be in the base 10 exponential form eN or *^N,
    where N is an integer.

    Parameters:
    - file_path, path to the file.
    - data, one-dimensional double-type array of the size rows*columns
    to output the data following the row-major order, where rows and columns
    may be obtained through csvdat_get_sizes(). The outputted data may be
    accessed through data[j + columns*i], where i is any row and j is
    any column.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void csvdat_import(const char *file_path,
    double * data) {
    
    sepdat_import_impl_(file_path, data, ',');
}

/*
    Imports 'double complex'-type data from a Comma-Separated Values data file
    and stores the values in an one-dimensional 'double complex'-type array
    following the row-major order. The complex values may be of the type a,
    a+bi, bi, and i, where i may also be j, *i, *j, or *I, and where a and
    b may also be in the base 10 exponential form eN or *^N, where N is an
    integer.

    Parameters:
    - file_path, path to the file.
    - data, one-dimensional 'double complex'-type array of the size
    rows*columns to output the data following the row-major order, where rows
    and columns may be obtained through csvdat_get_sizes().
    The outputted data may be accessed through data[j + columns*i],
    where i is any row and j is any column.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void csvdat_import_cplx(const char *file_path,
    tpdcomplex_impl_ *data) {
    
    sepdat_import_cplx_impl_(file_path, data, ',');
}

/*
    Exports double-type data of an one-dimensional
    double-type array, following the row-major order, to a Comma-Separated
    Values data file.

    Parameters:
    - file_path, path to the file.
    - data, one-dimensional double-type array of the size rows*columns
    containing the data. The data is accessed following the row-major order,
    i.e., through data[j + columns*i], where i is any row and j is any
    column.
    - rows, number of rows of the data.
    - columns, number of columns of the data.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void csvdat_export(const char *file_path,
    const double *data, int rows, int columns) {

    sepdat_export_impl_(file_path, data, rows, columns, ',');
}

/*
    Exports 'double complex'-type data of an
    one-dimensional 'double complex'-type array,
    following the row-major
    order, to a Comma-Separated Values data file.
    The exported complex values are of the type a+bi.

    Parameters:
    - file_path, path to the file.
    - data, one-dimensional 'double complex'-type array of the size
    rows*columns containing the data. The data is accessed following the
    row-major order, i.e., through data[j + columns*i], where i is any
    row and j is any column.
    - rows, number of rows of the data.
    - columns, number of columns of the data.
*/
DATA_FILE_LIBRARY_STATIC_INLINE_IMPL_
void csvdat_export_cplx(const char *file_path,
    const tpdcomplex_impl_ *data, int rows, int columns) {

    sepdat_export_cplx_impl_(file_path, data, rows, columns, ',');
}

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* DATA_FILE_LIBRARY_CSVDAT_H */