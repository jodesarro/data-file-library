/*
  Data File Library: A set of C functions for handling numeric data files

  Repository: <https://github.com/jodesarro/data-file-library>
  License: Refer to the LICENSE file in the Repository
  Language standard: C99

  Description: Functions for handling files having a structure in which lines
  are separated by line break and columns are separated by tabular spacing.
*/

#ifndef DATA_FILE_LIBRARY_TSVDAT_H
#define DATA_FILE_LIBRARY_TSVDAT_H

#include "../impl/api_impl_.h"
#include "../impl/cplx_c_cpp_impl_.h"

#ifndef DATA_FILE_LIBRARY_IMPORTS
#include "../impl/sepdat_impl_.h"
#endif

DATA_FILE_LIBRARY_API_IMPL_
/*
  Gets the size in each dimension (number of rows and columns) from a
  Tab-Separated data file.

  Parameters:
  - file_path, path to the file.
  - &rows, to output the number of rows.
  - &columns, to output the number of columns.
*/
void tsvdat_get_sizes(const char *file_path, int *rows, int *columns)
#ifndef DATA_FILE_LIBRARY_IMPORTS
{
  sepdat_get_sizes_impl_(file_path, rows, columns, ',');
}
#else
    ;
#endif

DATA_FILE_LIBRARY_API_IMPL_
/*
  Imports double-type data from a Tab-Separated Values data file and stores in
  an one-dimensional double-type array following the row-major order. The values
  may also be in the base 10 exponential form eN or *^N, where N is an integer.

  Parameters:
  - file_path, path to the file.
  - data, one-dimensional double-type array of the size rows*columns to output
  the data following the row-major order, where rows and columns may be obtained
  through tsvdat_get_sizes(). The outputted data may be accessed through data[j
  + columns*i], where i is any row and j is any column.

  Details: It prints a progress bar whenever the macro
  DATA_FILE_LIBRARY_PROGRESS_BAR is defined.
*/
void tsvdat_import(const char *file_path, double *data)
#ifndef DATA_FILE_LIBRARY_IMPORTS
{
  sepdat_import_impl_(file_path, data, ',');
}
#else
    ;
#endif

DATA_FILE_LIBRARY_API_IMPL_
/*
  Imports complex value data from a Tab-Separated Values data file and
  stores the values in an one-dimensional complex value array following
  the row-major order. The complex values may be of the type a, a+bi, bi, and i,
  where i may also be j, *i, *j, or *I, and where a and b may also be in the
  base 10 exponential form eN or *^N, where N is an integer.

  Parameters:
  - file_path, path to the file.
  - data, one-dimensional complex value array of the size rows*columns
  to output the data following the row-major order, where rows and columns may
  be obtained through tsvdat_get_sizes(). The outputted data may be accessed
  through data[j + columns*i], where i is any row and j is any column.

  Details: It prints a progress bar whenever the macro
  DATA_FILE_LIBRARY_PROGRESS_BAR is defined.
*/
void tsvdat_import_cplx(const char *file_path, dcomplex *data)
#ifndef DATA_FILE_LIBRARY_IMPORTS
{
  sepdat_import_cplx_impl_(file_path, data, ',');
}
#else
    ;
#endif

DATA_FILE_LIBRARY_API_IMPL_
/*
  Exports double-type data of an one-dimensional double-type array, following
  the row-major order, to a Tab-Separated Values data file.

  Parameters:
  - file_path, path to the file.
  - data, one-dimensional double-type array of the size rows*columns containing
  the data. The data is accessed following the row-major order, i.e., through
  data[j + columns*i], where i is any row and j is any column.
  - rows, number of rows of the data.
  - columns, number of columns of the data.

  Details: It prints a progress bar whenever the macro
  DATA_FILE_LIBRARY_PROGRESS_BAR is defined.
*/
void tsvdat_export(const char *file_path, const double *data, int rows,
                   int columns)
#ifndef DATA_FILE_LIBRARY_IMPORTS
{
  sepdat_export_impl_(file_path, data, rows, columns, ',');
}
#else
    ;
#endif

DATA_FILE_LIBRARY_API_IMPL_
/*
  Exports complex value data of an one-dimensional complex value
  array, following the row-major order, to a Tab-Separated Values data file. The
  exported complex values are of the type a+bi.

  Parameters:
  - file_path, path to the file.
  - data, one-dimensional complex value array of the size rows*columns
  containing the data. The data is accessed following the row-major order, i.e.,
  through data[j + columns*i], where i is any row and j is any column.
  - rows, number of rows of the data.
  - columns, number of columns of the data.

  Details: It prints a progress bar whenever the macro
  DATA_FILE_LIBRARY_PROGRESS_BAR is defined.
*/
void tsvdat_export_cplx(const char *file_path, const dcomplex *data, int rows,
                        int columns)
#ifndef DATA_FILE_LIBRARY_IMPORTS
{
  sepdat_export_cplx_impl_(file_path, data, rows, columns, ',');
}
#else
    ;
#endif

#endif /* DATA_FILE_LIBRARY_TSVDAT_H */