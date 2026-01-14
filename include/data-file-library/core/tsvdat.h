/* 
    Data File Library: A set of C functions for handling numeric data files

    File: include/data-file-library/core/tsvdat.h
    Version: include/data-file-library/version.h
    Author: Jhonas Olivati de Sarro
    Language standards: C99 with guards for C++98 compatibility
    License: include/data-file-library/license.txt

    Description:
        Functions for handling files having a structure in which lines are
        separated by line break and columns are separated by tabular spacing.
*/

#ifndef DATA_FILE_LIBRARY_TSVDAT_H
#define DATA_FILE_LIBRARY_TSVDAT_H

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
    Gets the size in each dimension (number of rows and columns) of a
    Tab-Separated data file.

    Parameters:
    - tsvdat_path, path to the file.
    - &rows, for storing the number of rows.
    - &columns, for storing the number of columns.
*/
static inline void tsvdat_get_sizes(const char *tsvdat_path, int *rows,
    int *columns) {
    
    sepdat_get_sizes_impl_(tsvdat_path, rows, columns, ',');
}

/*
    Imports double-type data from a Tab-Separated data file and
    store the values in an one-dimensional double-type array. The values may
    also be in the base 10 exponential form eN or *^N, where N is an integer.

    Parameters:
    - tsvdat_path, path to the file.
    - data_array, one-dimensional double-type array of the size rows*columns
    for storing the data. The array must have rows*columns size, where rows
    and columns may be obtained through tsvdat_get_sizes(). Its data may be
    accessed through data_array[i + rows*j], where i is any row and j is any
    column.
*/
static inline void tsvdat_import(const char *tsvdat_path,
    double * data_array) {
    
    sepdat_import_impl_(tsvdat_path, data_array, ',');
}

/*
    Imports complex-type data from a Tab-Separated data file and
    store the values in an one-dimensional complex-type array. The complex
    values may be of the type a, a+bi, bi, i, and -i, where i may also be j,
    *i, *j, or *I, and where a and b may also be in the base 10 exponential
    form eN or *^N, where N is an integer.

    Parameters:
    - tsvdat_path, path to the file.
    - data_array, one-dimensional complex-type array of the size rows*columns
    for storing the data. The array must have rows*columns size, where rows
    and columns may be obtained through tsvdat_get_sizes(). Its data may be
    accessed through data_array[i + rows*j], where i is any row and j is any
    column.
*/
static inline void tsvdat_import_cplx(const char *tsvdat_path,
    tpdcomplex_impl_ *data_array) {
    
    sepdat_import_cplx_impl_(tsvdat_path, data_array, ',');
}

/*
    Exports double-type data of an one-dimensional double-type array to a
    Tab-Separated data file.

    Parameters:
    - tsvdat_path, path to the file.
    - data_array, one-dimensional double-type array of the size rows*columns
    containing the data. The data is accessed through data_array[i + rows*j],
    where i is a row and j is a column.
    - rows, number of rows of the data.
    - columns, number of columns of the data.
*/
static inline void tsvdat_export(const char *tsvdat_path,
    const double *data_array, int rows, int columns) {

    sepdat_export_impl_(tsvdat_path, data_array, rows, columns, ',');
}

/*
    Exports complex-type data of an one-dimensional complex-type array to a
    Tab-Separated data file. The exported complex values are of the type a+bi.

    Parameters:
    - tsvdat_path, path to the file.
    - data_array, one-dimensional complex-type array of the size rows*columns
    containing the data. The data is accessed through data_array[i + rows*j],
    where i is a row and j is a column.
    - rows, number of rows of the data.
    - columns, number of columns of the data.
*/
static inline void tsvdat_export_cplx(const char *tsvdat_path,
    const tpdcomplex_impl_ *data_array, int rows, int columns) {

    sepdat_export_cplx_impl_(tsvdat_path, data_array, rows, columns, ',');
}

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* DATA_FILE_LIBRARY_TSVDAT_H */