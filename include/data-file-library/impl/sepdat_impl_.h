/* 
    Data File Library: A set of C functions for handling numeric data files

    File: include/data-file-library/impl/sepdat_impl_.h
    Version: include/data-file-library/version.h
    Author: Jhonas Olivati de Sarro
    Language standards: C99 with guards for C++98 compatibility
    License: include/data-file-library/license.txt

    Description:
        Implementation of functions for handling files having a structure in
        which lines are separated by line breaks and columns are separated by
        any given separator.
*/

#ifndef DATA_FILE_LIBRARY_SEPDAT_IMPL_H
#define DATA_FILE_LIBRARY_SEPDAT_IMPL_H

#ifdef __cplusplus

/* Includes, typedefs and/or macros for C++98 compatibility */

#include <complex> /* For complex numbers */
typedef std::complex<double> tpdcomplex_impl_;
#define creal(z) std::real(z)
#define cimag(z) std::imag(z)

extern "C" {

#else

#include <complex.h> /* For complex numbers */
typedef double complex tpdcomplex_impl_;

#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h> /* For EXIT_FAILURE */
#include "parse_impl_.h"

/*
    Implementation for getting the size in each dimension (number of rows and
    columns) of a data file with a given column separator.

    Parameters:
    - sepdat_path, path to the data file.
    - &rows, for storing the number of rows.
    - &columns, for storing the number of columns.
    - sep, column separator.
*/
static inline void sepdat_get_sizes_impl_(const char *sepdat_path, int *rows,
    int *columns, char sep) {

    /* Open file */
    FILE *file = fopen(sepdat_path, "r");
    if (!file) {
        fprintf(stderr, "[DATA-FILE-LIBRARY WARNING]"
                        " sepdat_get_sizes_impl_() ->"
                        " Error in opening file: %s."
                        " Exiting.", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Read file */
    int ch;
    int current_cols = 0;
    int max_cols = 0;
    *rows = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == sep) {
            current_cols++;
        }
        else if (ch == '\n') {
            current_cols++;
            if (current_cols > max_cols) {
                max_cols = current_cols;
            }
            current_cols = 0;
            (*rows)++;
        }
    }

    /* Handle last row if file does not end with newline */
    if (current_cols > 0) {
        current_cols++;
        if (current_cols > max_cols) {
            max_cols = current_cols;
        }
        (*rows)++;
    }
    *columns = max_cols;

    /* Close file */
    fclose(file);
}

/*
    Implementation for importing double-type data from a breakline-separated
    lines and char-separated data file and store the values in an
    one-dimensional double-type array. The values may also be in the base 10
    exponential form eN or *^N, where N is an integer.

    Parameters:
    - sepdat_path, path to the file.
    - data_array, one-dimensional double-type array of the size rows*columns for
    storing the data. The array must have rows*columns size, where rows and
    columns may be obtained through sepdat_get_sizes(). Its data may be
    accessed through data_array[i + rows*j], where i is any row and j is any
    column.
    - sep, column separator.
*/
static inline void sepdat_import_impl_(const char *sepdat_path,
    double *data_array, char sep) {

    /* Count rows and columns */
    int rows;
    int columns;
    sepdat_get_sizes_impl_(sepdat_path, &rows, &columns, sep);

    /* Open file */
    FILE *file = fopen(sepdat_path, "r");
    if (!file) {
        fprintf(stderr, "[DATA-FILE-LIBRARY WARNING]"
                        " sepdat_import_impl_() ->"
                        " Error in opening file: %s."
                        " Exiting.", strerror(errno));
        exit(EXIT_FAILURE);
    }
   
    int i = 0, j = 0;
    char buffer[128], fmt[32];
    snprintf(fmt, sizeof(fmt), "%%127[^%c\n]", sep); /* "%127[^<sep>\n]" */

    /* Read file */
    while (fscanf(file, fmt, buffer) == 1) {
        /* Parse and store */
        data_array[i + rows * j ] = parse_real_impl_(buffer);
        /* Look ahead for separator */
        int ch = fgetc(file);
        if (ch == sep) {
            j++;
        }
        else if (ch == '\n' || ch == EOF) {
            i++;
            j = 0;
        }
        if (i == rows && j == columns ) break;
    }

    /* Close file */
    fclose(file);
}

/*
    Implementation for importing complex-type data from a breakline-separated
    lines and char-separated data file and store the values in an
    one-dimensional complex-type array. The complex values may be of the type a,
    a+bi, bi, i, and -i, where i may also be j, *i, *j, or *I, and where a and
    b may also be in the base 10 exponential form eN or *^N, where N is an
    integer.

    Parameters:
    - sepdat_path, path to the file.
    - data_array, one-dimensional complex-type array of the size rows*columns
    for storing the data. The array must have rows*columns size, where rows
    and columns may be obtained through sepdat_get_sizes(). Its data may be
    accessed through data_array[i + rows*j], where i is any row and j is any
    column.
    - sep, column separator.
*/
static inline void sepdat_import_cplx_impl_(const char *sepdat_path,
    tpdcomplex_impl_ *data_array, char sep) {
    
    /* Count rows and columns */
    int rows;
    int columns;
    sepdat_get_sizes_impl_(sepdat_path, &rows, &columns, sep);

    /* Open file */
    FILE *file = fopen(sepdat_path, "r");
    if (!file) {
        fprintf(stderr, "[DATA-FILE-LIBRARY WARNING]"
                        " sepdat_import_cplx_impl_() ->"
                        " Error in opening file: %s."
                        " Exiting.", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int i = 0, j = 0;
    char buffer[128], fmt[32];
    snprintf(fmt, sizeof(fmt), "%%127[^%c\n]", sep); /* "%127[^<sep>\n]" */
    
    /* Read file */
    while (fscanf(file, fmt, buffer) == 1 ) {
        /* Parse and store */
        data_array[i + rows * j ] = parse_complex_impl_(buffer);
        /* Look ahead for separator */
        int ch = fgetc(file);
        if (ch == sep) {
            j++;
        }
        else if (ch == '\n' || ch == EOF) {
            i++;
            j = 0;
        }
        if (i == rows && j == columns ) break;
    }

    /* Close file */
    fclose(file);
}

/*
    Implementation for exporting double-type data of an one-dimensional
    double-type array to a breakline-separated lines and char-separated
    columns data file.

    Parameters:
    - sepdat_path, path to the file.
    - data_array, one-dimensional double-type array of the size rows*columns
    containing the data. The data is accessed through data_array[i + rows*j],
    where i is a row and j is a column.
    - rows, number of rows of the data.
    - columns, number of columns of the data.
    - sep, column separator.
*/
static inline void sepdat_export_impl_(const char *sepdat_path,
    const double *data_array, int rows, int columns, char sep) {

    /* Open file */
    FILE *file = fopen(sepdat_path, "w");
    if (!file) {
        fprintf(stderr, "[DATA-FILE-LIBRARY WARNING]"
                        " sepdat_export_impl_() ->"
                        " Error in opening file: %s."
                        " Exiting.", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            fprintf(file, "%.16e", data_array[i + rows * j]);
            if (j < columns - 1) {
                fputc(sep, file);  /* Tab between columns */
            }
        }
        fputc('\n', file);  /* Newline at end of row */
    }

    /* Close file */
    fclose(file);
}

/*
    Implementation for exporting complex-type data of an one-dimensional
    complex-type array to a breakline-separated lines and char-separated
    columns data file. The exported complex values are of the type a+bi.

    Parameters:
    - sepdat_path, path to the file.
    - data_array, one-dimensional complex-type array of the size rows*columns
    containing the data. The data is accessed through data_array[i + rows*j],
    where i is a row and j is a column.
    - rows, number of rows of the data.
    - columns, number of columns of the data.
    - sep, column separator.
*/
static inline void sepdat_export_cplx_impl_(const char *sepdat_path,
    const tpdcomplex_impl_ *data_array, int rows, int columns, char sep) {

    /* Open file */
    FILE *file = fopen(sepdat_path, "w");
    if (!file) {
        fprintf(stderr, "[DATA-FILE-LIBRARY WARNING]"
                        " sepdat_export_cplx_impl_() ->"
                        " Error in opening file: %s."
                        " Exiting.", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            fprintf(file, "%.16e%+.16ei", creal(data_array[i + rows * j]),
                    cimag(data_array[i + rows * j]));
            if (j < columns - 1) {
                fputc(sep, file);  /* Tab between columns */
            }
        }
        fputc('\n', file);  /* Newline at end of row */
    }

    /* Close file */
    fclose(file);
}

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* DATA_FILE_LIBRARY_SEPDAT_IMPL_H */