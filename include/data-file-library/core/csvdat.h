/*
  Data File Library: A set of C functions for handling numeric data files

  File: include/data-file-library/core/csvdat.h
  Version: include/data-file-library/version.h
  Author: Jhonas Olivati de Sarro
  Language standards: C99
  License: include/data-file-library/license.txt

  Description: Functions for handling files having a structure in which lines
  are separated by line break and columns are separated by comma.
*/

#ifndef DATA_FILE_LIBRARY_CSVDAT_H
#define DATA_FILE_LIBRARY_CSVDAT_H

#include "../impl/api_impl_.h"
#include "../impl/cplx_c_cpp_impl_.h"

#ifndef DATA_FILE_LIBRARY_IMPORTS
#include "../impl/sepdat_impl_.h"
#endif

/*
  Gets the size in each dimension (number of rows and columns) from a
  Comma-Separated Values data file.

  Parameters:
  - file_path, path to the file.
  - &rows, to output the number of rows.
  - &columns, to output the number of columns.
*/
DATA_FILE_LIBRARY_API_IMPL_
void csvdat_get_sizes(const char *file_path, int *rows, int *columns)
#ifndef DATA_FILE_LIBRARY_IMPORTS
{
  sepdat_get_sizes_impl_(file_path, rows, columns, ',');
}
#else
    ;
#endif

/*
  Imports double-type data from a Comma-Separated Values data file and stores in
  an one-dimensional double-type array following the row-major order. The values
  may also be in the base 10 exponential form eN or *^N, where N is an integer.

  Parameters:
  - file_path, path to the file.
  - data, one-dimensional double-type array of the size rows*columns to output
  the data following the row-major order, where rows and columns may be obtained
  through csvdat_get_sizes(). The outputted data may be accessed through data[j
  + columns*i], where i is any row and j is any column.
*/
DATA_FILE_LIBRARY_API_IMPL_
void csvdat_import(const char *file_path, double *data)
#ifndef DATA_FILE_LIBRARY_IMPORTS
{
  sepdat_import_impl_(file_path, data, ',');
}
#else
    ;
#endif

/*
  Imports 'double complex'-type data from a Comma-Separated Values data file and
  stores the values in an one-dimensional 'double complex'-type array following
  the row-major order. The complex values may be of the type a, a+bi, bi, and i,
  where i may also be j, *i, *j, or *I, and where a and b may also be in the
  base 10 exponential form eN or *^N, where N is an integer.

  Parameters:
  - file_path, path to the file.
  - data, one-dimensional 'double complex'-type array of the size rows*columns
  to output the data following the row-major order, where rows and columns may
  be obtained through csvdat_get_sizes(). The outputted data may be accessed
  through data[j + columns*i], where i is any row and j is any column.
*/
DATA_FILE_LIBRARY_API_IMPL_
void csvdat_import_cplx(const char *file_path, tpdfcplx_impl_ *data)
#ifndef DATA_FILE_LIBRARY_IMPORTS
{
  sepdat_import_cplx_impl_(file_path, data, ',');
}
#else
    ;
#endif

/*
  Exports double-type data of an one-dimensional double-type array, following
  the row-major order, to a Comma-Separated Values data file.

  Parameters:
  - file_path, path to the file.
  - data, one-dimensional double-type array of the size rows*columns containing
  the data. The data is accessed following the row-major order, i.e., through
  data[j + columns*i], where i is any row and j is any column.
  - rows, number of rows of the data.
  - columns, number of columns of the data.
*/
DATA_FILE_LIBRARY_API_IMPL_
void csvdat_export(const char *file_path, const double *data, int rows,
                   int columns)
#ifndef DATA_FILE_LIBRARY_IMPORTS
{
  sepdat_export_impl_(file_path, data, rows, columns, ',');
}
#else
    ;
#endif

/*
  Exports 'double complex'-type data of an one-dimensional 'double complex'-type
  array, following the row-major order, to a Comma-Separated Values data file.
  The exported complex values are of the type a+bi.

  Parameters:
  - file_path, path to the file.
  - data, one-dimensional 'double complex'-type array of the size rows*columns
  containing the data. The data is accessed following the row-major order, i.e.,
  through data[j + columns*i], where i is any row and j is any column.
  - rows, number of rows of the data.
  - columns, number of columns of the data.
*/
DATA_FILE_LIBRARY_API_IMPL_
void csvdat_export_cplx(const char *file_path, const tpdfcplx_impl_ *data,
                        int rows, int columns)
#ifndef DATA_FILE_LIBRARY_IMPORTS
{
  sepdat_export_cplx_impl_(file_path, data, rows, columns, ',');
}
#else
    ;
#endif

#endif /* DATA_FILE_LIBRARY_CSVDAT_H */