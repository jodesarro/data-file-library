/* 
    Data File Library: A set of C functions for handling numeric data files

    File: include/data-file-library/impl/wldat_impl_.h
    Version: include/data-file-library/version.h
    Author: Jhonas Olivati de Sarro
    Language standards: C99 with guards for C++98 compatibility
    License: include/data-file-library/license.txt

    Description:
        Implementation of functions for handling files having the structure of
        a Wolfram Language file format (nested braces).
*/

#ifndef DATA_FILE_LIBRARY_WLDAT_IMPL_H
#define DATA_FILE_LIBRARY_WLDAT_IMPL_H

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
#include <ctype.h>
#include "parse_impl_.h"

/*
    Implementation for returning the size of the comment of a Wolfram
    Language file format, i.e., the number of characters of the first line of
    the file plus a '\0' char.

    Parameters:
    - wldat_path, path to the file.
*/
static inline int wldat_get_comment_size_impl_(const char *wldat_path) {
    
    /* Open file */
    FILE *file = fopen(wldat_path, "r");
    if (!file) {
        fprintf(stderr, "[DATA-FILE-LIBRARY WARNING]"
                        " wldat_get_comment_size_impl_() ->"
                        " Error in opening file: %s."
                        " Exiting.", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int ch, count = 0;

    /* Read characters until newline or EOF */
    while ((ch = fgetc(file)) != EOF && (char)ch != '\n') {
        count++;
    }
    /* Close file */
    fclose(file);

    /* Return */
    return count + 1;
}

/*
    Implementation for getting the comment of a Wolfram Language file format,
    i.e., the text of the whole first line plus a '\0' char.

    Parameters:
    - wldat_path, path to the file.
    - comment, array of size wldat_get_comment_size_impl_(wldat_path) to store
    the text.
*/
static inline void wldat_get_comment_impl_(const char *wldat_path,
    char *comment) {
    
    /* Get the size of the comment */
    int comment_size = wldat_get_comment_size_impl_(wldat_path);

    /* Open file */
    FILE *file = fopen(wldat_path, "r");
    if (!file) {
        fprintf(stderr, "[DATA-FILE-LIBRARY WARNING]"
                        " wldat_get_comment_impl_() ->"
                        " Error in opening file: %s."
                        " Exiting.", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Read the first line */
    fgets(comment, comment_size, file);

    /* Close file */
    fclose(file);
}

/*
    Implementation for returning the number of dimensions of a Wolfram
    Language file format. The number of dimensions must not exceed 128.

    Parameters:
    - wldat_path, path to the file.
*/
static inline int wldat_get_dimensions_impl_(const char *wldat_path) {

    /* Open file */
    FILE *file = fopen(wldat_path, "r");
    if (!file) {
        fprintf(stderr, "[DATA-FILE-LIBRARY WARNING]"
                        " wldat_get_dimensions_impl_() ->"
                        " Error in opening file: %s."
                        " Exiting.", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int ch, count = 0;

    /* Skip the first line */
    while ((ch = fgetc(file)) != EOF) {
        if ((char)ch == '\n') {
            break;
        }
    }

    /* Read the second line and count '{' */
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') break;   /* Stop at end of second line */
        if (ch == '{') {
            count++;
        }
        else {
            break;
        }
    }

    /* Close file */
    fclose(file);
    
    /* Return */
    if (count > 128) {
        fprintf(stderr, "[DATA-FILE-LIBRARY WARNING]"
                        " wldat_get_dimensions_impl_() ->"
                        " Error: Dimensions must not exceed 128.");
        exit(EXIT_FAILURE);
    }
    else {
        return count;
    }
}

/*
    Implementation for getting the size of each dimension of a Wolfram
    Language file format.

    Parameters:
    - wldat_path, path to the file.
    - sizes, array of size wldat_get_dimensions_impl_(wldat_path) to
    sequentially store the size of each dimension. The size of this array must
    not exceed 128.
*/
static inline void wldat_get_sizes_impl_(const char *wldat_path, int *sizes) {

    /* Get dimensions */
    int dimensions = wldat_get_dimensions_impl_(wldat_path);

    /* Initialize counts */
    for (int i = 0; i < dimensions; i++) {
        sizes[i] = 1;
    }

    /* Open file */
    FILE *file = fopen(wldat_path, "r");
    if (!file) {
        fprintf(stderr, "[DATA-FILE-LIBRARY WARNING]"
                        " wldat_get_sizes_impl_() ->"
                        " Error in opening file: %s."
                        " Exiting.", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int ch;

    /* Skip the first line */
    while ((ch = fgetc(file)) != EOF) {
        if ((char)ch == '\n') {
            break;
        }
    }

    /* Build target and stop strings for each level */
    char targets[128][128];
    char stops[128][128];
    for (int i = 0; i < dimensions; i++) {
        /* Target = i braces + ',' */
        for (int j = 0; j < i; j++) targets[i][j] = '}';
        targets[i][i] = ',';
        targets[i][i+1] = '\0';

        /* Stop = (i+1) braces */
        for (int j = 0; j < i+1; j++) stops[i][j] = '}';
        stops[i][i+1] = '\0';
    }

    /* Track which dimensions are still active */
    int active_dimensions = 0;

    char buffer[128];
    int buf_len = 0;

    while ((ch = fgetc(file)) != EOF && active_dimensions < dimensions) {
        /* Append to buffer */
        if (buf_len < (int)sizeof(buffer) - 1) {
            buffer[buf_len++] = (char)ch;
            buffer[buf_len] = '\0';
        }
        else {
            memmove(buffer, buffer + 1, buf_len - 1);
            buffer[buf_len - 1] = (char)ch;
        }

        /* Check stop for current level */
        int stop_len = strlen(stops[active_dimensions]);
        if (buf_len >= stop_len &&
            memcmp(buffer + buf_len - stop_len, stops[active_dimensions],
            stop_len) == 0) {
            
            active_dimensions++;   /* Move to next dimension */
            continue;
        }

        /* Check target for current dimension */
        int target_len = strlen(targets[active_dimensions]);
        if (buf_len >= target_len &&
            memcmp(buffer + buf_len - target_len, targets[active_dimensions],
            target_len) == 0) {
            
            sizes[dimensions - active_dimensions - 1]++;
        }
    }

    /* Close file */
    fclose(file);
}

/*
    Compute flat index in column-major order. Example, considering an array
    arr of two dimensions 0 <= i < IMAX and 0 <= j < JMAX, in the
    column-major order one can write arr[i + IMAX*j], with the size of arr
    being IMAX*JMAX.

    Parameters:
    - indices, array with the indices i.
    - sizes, array with the maximum value IMAX for each i.
    - dimensions, number of i's.
*/
static inline int column_major_flat_index_impl_(const int *indices,
    const int *sizes, int dimensions) {
    
    int idx = 0;
    for (int d = dimensions - 1; d >= 0; --d) {
        idx = indices[d] + sizes[d] * idx;
    }
    return idx;
}

/*
    Implementation for a recursive function for dealing with nested braces
    of a Wolfram Language file format with real numbers.

    Parameters:
    - file, file with the data, already read until the first '\n'.
    - level, level of the nested brace.
    - dimensions, number of dimensions of the data.
    - sizes, array with the size of each dimension.
    - indices, array with the indices of each dimension.
    - data_array, array to store the results.
*/
static inline void read_nested_braces_impl_(FILE *file, int level,
    int dimensions, const int *sizes, int *indices, double *data_array) {
    
    int ch;
    char buf[128];
    int buf_i = 0;
    int element_count = 0;

    /* Expect '{' */
    do { ch = fgetc(file); } while (ch != EOF && isspace(ch));
    if (ch != '{') return;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '{') {
            ungetc(ch, file);
            indices[level] = element_count;
            read_nested_braces_impl_(file, level + 1, dimensions, sizes,
                indices, data_array);
            element_count++;
        }
        else if (ch == '}') {
            if (buf_i > 0) {
                buf[buf_i] = '\0';
                indices[level] = element_count;
                int idx = column_major_flat_index_impl_(indices, sizes,
                    dimensions);
                data_array[idx] = parse_real_impl_(buf);
                buf_i = 0;
                element_count++;
            }
            break;
        }
        else if (ch == ',') {
            if (buf_i > 0) {
                buf[buf_i] = '\0';
                indices[level] = element_count;
                int idx = column_major_flat_index_impl_(indices, sizes,
                    dimensions);
                data_array[idx] = parse_real_impl_(buf);
                buf_i = 0;
                element_count++;
            }
        }
        else if (!isspace(ch)) {
            buf[buf_i++] = (char)ch;
        }
    }
}

/*
    Implementation for a recursive function for dealing with nested braces
    of a Wolfram Language file format with complex numbers.

    Parameters:
    - file, file with the data, already read until the first '\n'.
    - level, level of the nested brace.
    - dimensions, number of dimensions of the data.
    - sizes, array with the size of each dimension.
    - indices, array with the indices of each dimension.
    - data_array, array to store the results.
*/
static inline void read_nested_braces_cplx_impl_(FILE *file, int level,
    int dimensions, const int *sizes, int *indices,
    tpdcomplex_impl_ *data_array) {
    
    int ch;
    char buf[128];
    int buf_i = 0;
    int element_count = 0;

    /* Expect '{' */
    do { ch = fgetc(file); } while (ch != EOF && isspace(ch));
    if (ch != '{') return;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '{') {
            ungetc(ch, file);
            indices[level] = element_count;
            read_nested_braces_cplx_impl_(file, level + 1, dimensions,
                sizes, indices, data_array);
            element_count++;
        }
        else if (ch == '}') {
            if (buf_i > 0) {
                buf[buf_i] = '\0';
                indices[level] = element_count;
                int idx = column_major_flat_index_impl_(indices, sizes,
                    dimensions);
                data_array[idx] = parse_complex_impl_(buf);
                buf_i = 0;
                element_count++;
            }
            break;
        }
        else if (ch == ',') {
            if (buf_i > 0) {
                buf[buf_i] = '\0';
                indices[level] = element_count;
                int idx = column_major_flat_index_impl_(indices, sizes,
                    dimensions);
                data_array[idx] = parse_complex_impl_(buf);
                buf_i = 0;
                element_count++;
            }
        }
        else if (!isspace(ch)) {
            buf[buf_i++] = (char)ch;
        }
    }
}

/*
    Implementation for importing data of real numbers of a Wolfram Language
    file format.

    Parameters:
    - wldat_path, path to the data file.
    - data_array, array of size S1*S2*...*SN to store the results, where
    N is the number of dimensions, and for each dimension n,
    where 1 <= n <= N, Sn is its size. Notice that N may be obtained through
    wldat_get_dimensions_impl_(wldat_path) and Sn through
    wldat_get_sizes_impl_(wldat_path).
*/
static inline void wldat_import_impl_(const char *wldat_path,
    double *data_array) {
    
    /* Get dimensions and sizes */
    int dimensions = wldat_get_dimensions_impl_(wldat_path);
    int sizes[128];
    wldat_get_sizes_impl_(wldat_path, sizes);

    /* Open file */
    FILE *file = fopen(wldat_path, "r");
    if (!file) {
        fprintf(stderr, "[DATA-FILE-LIBRARY WARNING]"
                        " wldat_import_impl_() ->"
                        " Error in opening file: %s."
                        " Exiting.", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int ch;

    /* Skip the first line */
    while ((ch = fgetc(file)) != EOF) {
        if ((char)ch == '\n') {
            break;
        }
    }

    int indices[128];
    read_nested_braces_impl_(file, 0, dimensions, sizes, indices,
        data_array);

    /* Close file */
    fclose(file);
}

/*
    Implementation for importing data of complex numbers of a Wolfram Language
    file format.

    Parameters:
    - wldat_path, path to the data file.
    - data_array, array of size S1*S2*...*SN to store the results, where
    N is the number of dimensions, and for each dimension n,
    where 1 <= n <= N, Sn is its size. Notice that N may be obtained through
    wldat_get_dimensions_impl_(wldat_path) and Sn through
    wldat_get_sizes_impl_(wldat_path).
*/
static inline void wldat_import_cplx_impl_(const char *wldat_path,
    tpdcomplex_impl_ *data_array) {
    
    /* Get dimensions and sizes */
    int dimensions = wldat_get_dimensions_impl_(wldat_path);
    int sizes[128];
    wldat_get_sizes_impl_(wldat_path, sizes);

    /* Open file */
    FILE *file = fopen(wldat_path, "r");
    if (!file) {
        fprintf(stderr, "[DATA-FILE-LIBRARY WARNING]"
                        " wldat_import_cplx_impl_() ->"
                        " Error in opening file: %s."
                        " Exiting.", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int ch;

    /* Skip the first line */
    while ((ch = fgetc(file)) != EOF) {
        if ((char)ch == '\n') {
            break;
        }
    }

    int indices[128];
    read_nested_braces_cplx_impl_(file, 0, dimensions, sizes, indices,
        data_array);

    /* Close file */
    fclose(file);
}

/*
    Implementation for a recursive function for writing nested braces
    of a Wolfram Language file format with real numbers.

    Parameters:
    - file, file with the data, already read until the first '\n'.
    - level, level of the nested brace.
    - dimensions, number of dimensions of the data.
    - sizes, array with the size of each dimension.
    - indices, array with the indices of each dimension.
    - data_array, array to store the results.
*/
static inline void write_nested_braces_impl_(FILE *file, int level,
    int dimensions, const int *sizes, int *indices,
    const double *data_array) {

    fprintf(file, "{");
    for (int i = 0; i < sizes[level]; i++) {
        indices[level] = i;
        if (level == dimensions - 1) {
            /* Deepest level -> print number */
            int idx = column_major_flat_index_impl_(indices, sizes,
                dimensions);
            char buf[128];
            e_to_star_caret_impl_(buf, sizeof(buf), data_array[idx]);
            fprintf(file, "%s", buf);
        }
        else {
            /* Recurse into next level */
            write_nested_braces_impl_(file, level + 1, dimensions,
                sizes, indices, data_array);
        }
        if (i < sizes[level] - 1) fprintf(file, ", ");
    }
    fprintf(file, "}");
}

/*
    Implementation for a recursive function for writing nested braces
    of a Wolfram Language file format with complex numbers.

    Parameters:
    - file, file with the data, already read until the first '\n'.
    - level, level of the nested brace.
    - dimensions, number of dimensions of the data.
    - sizes, array with the size of each dimension.
    - indices, array with the indices of each dimension.
    - data_array, array to store the results.
*/
static inline void write_nested_braces_cplx_impl_(FILE *file, int level,
    int dimensions, const int *sizes, int *indices,
    const tpdcomplex_impl_ *data_array) {

    fprintf(file, "{");
    for (int i = 0; i < sizes[level]; i++) {
        indices[level] = i;
        if (level == dimensions - 1) {
            /* Deepest level -> print number */
            int idx = column_major_flat_index_impl_(indices, sizes,
                dimensions);
            char buf_re[128], buf_abs_im[128];
            e_to_star_caret_impl_(buf_re, sizeof(buf_re),
                creal(data_array[idx]));
            e_to_star_caret_impl_(buf_abs_im, sizeof(buf_abs_im),
                fabs(cimag(data_array[idx])));
            if (cimag(data_array[idx]) < 0.0) {
                fprintf(file, "%s - %s*I", buf_re, buf_abs_im);
            }
            else {
                fprintf(file, "%s + %s*I", buf_re, buf_abs_im);
            }
        }
        else {
            /* Recurse into next level */
            write_nested_braces_cplx_impl_(file, level + 1, dimensions,
                sizes, indices, data_array);
        }
        if (i < sizes[level] - 1) fprintf(file, ", ");
    }
    fprintf(file, "}");
}

/*
    Implementation for exporting data of real numbers to a Wolfram Language
    file format with.

    Parameters:
    - wldat_path, path to the data file.
    - data_array, array of size S1*S2*...*SN to store the results, where
    N is the number of dimensions, and for each dimension n,
    where 1 <= n <= N, Sn is its size.
    - dimensions, number of the dimensions of the data.
    - sizes, array with the size of each dimension.
    - comment, text to be stored at the very first line of the file.
*/
static inline void wldat_export_impl_(const char *wldat_path,
    double *data_array, int dimensions, int *sizes, char *comment) {

    /* Open file */
    FILE *file = fopen(wldat_path, "w");
    if (!file) {
        fprintf(stderr, "[DATA-FILE-LIBRARY WARNING]"
                        " wldat_export_impl_() ->"
                        " Error in opening file: %s."
                        " Exiting.", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (comment == NULL || comment[0] == '\0' ) {
        fprintf(file, "(* Created with Data File Library:"
            " <https://github.com/jodesarro/data-file-library> *)\n");
    }
    else {
        fprintf(file, "(* %s *)\n", comment);
    }

    int indices[128];
    write_nested_braces_impl_(file, 0, dimensions, sizes, indices,
        data_array);

    /* Break line */
    fprintf(file, "\n");

    /* Close file */
    fclose(file);
}

/*
    Implementation for exporting data of complex numbers to a Wolfram Language
    file format with.

    Parameters:
    - wldat_path, path to the data file.
    - data_array, array of size S1*S2*...*SN to store the results, where
    N is the number of dimensions, and for each dimension n,
    where 1 <= n <= N, Sn is its size.
    - dimensions, number of the dimensions of the data.
    - sizes, array with the size of each dimension.
    - comment, text to be stored at the very first line of the file.
*/
static inline void wldat_export_cplx_impl_(const char *wldat_path,
    tpdcomplex_impl_ *data_array, int dimensions, int *sizes, char *comment) {

    /* Open file */
    FILE *file = fopen(wldat_path, "w");
    if (!file) {
        fprintf(stderr, "[DATA-FILE-LIBRARY WARNING]"
                        " wldat_export_cplx_impl_() ->"
                        " Error in opening file: %s."
                        " Exiting.", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (comment == NULL || comment[0] == '\0' ) {
        fprintf(file, "(* Created with Data File Library:"
            " <https://github.com/jodesarro/data-file-library> *)\n");
    }
    else {
        fprintf(file, "(* %s *)\n", comment);
    }

    int indices[128];
    write_nested_braces_cplx_impl_(file, 0, dimensions, sizes, indices,
        data_array);

    /* Break line */
    fprintf(file, "\n");

    /* Close file */
    fclose(file);
}

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* DATA_FILE_LIBRARY_WLDAT_IMPL_H */