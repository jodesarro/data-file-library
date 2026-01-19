/* 
    Data File Library: A set of C functions for handling numeric data files

    File: include/data-file-library/impl/wldat_impl_.h
    Version: include/data-file-library/version.h
    Author: Jhonas Olivati de Sarro
    Language standards: C99
    License: include/data-file-library/license.txt

    Description:
        Implementation of functions for handling files having the structure of
        a Wolfram Language package source format (nested braces).
*/

#ifndef DATA_FILE_LIBRARY_WLDAT_IMPL_H
#define DATA_FILE_LIBRARY_WLDAT_IMPL_H

#include <stdio.h> /* For fopen(), fclose(), fprintf(), ... */
#include <stdlib.h> /* For EXIT_FAILURE */
#include <ctype.h> /* For isspace() */
#include "cplx_c_cpp_impl_.h"
#include "parse_impl_.h"

/*
    Implementation for returning the size of the comment from a Wolfram
    Language package source format, i.e., the number of characters of the
    first line of the file plus a '\0' char.

    Parameter:
    - file_path, path to the file.
*/
static inline int wldat_get_comment_size_impl_(const char *file_path) {
    
    /* Open file */
    FILE *file = fopen(file_path, "r");
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
    Implementation for getting the comment from a Wolfram Language package
    source format, i.e., the text of the whole first line of the file plus
    a '\0' char.

    Parameters:
    - file_path, path to the file.
    - comment, array of size given by wldat_get_comment_size_impl_(), to
    output the text.
*/
static inline void wldat_get_comment_impl_(const char *file_path,
    char *comment) {
    
    /* Get the size of the comment */
    int comment_size = wldat_get_comment_size_impl_(file_path);

    /* Open file */
    FILE *file = fopen(file_path, "r");
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
    Implementation for returning the number of dimensions from a Wolfram
    Language package source format.
    The number of dimensions is limited to 128.

    Parameter:
    - file_path, path to the file.
*/
static inline int wldat_get_dimensions_impl_(const char *file_path) {

    /* Open file */
    FILE *file = fopen(file_path, "r");
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
                        " Error: Dimensions exceed 128.");
        exit(EXIT_FAILURE);
    }
    else {
        return count;
    }
}

/*
    Implementation for getting the size of each dimension from a Wolfram
    Language package source format.

    Parameters:
    - file_path, path to the file.
    - size, array of size given by wldat_get_dimensions_impl_(), to
    sequentially output the size of each dimension. The size of this array
    is limited to 128.
*/
static inline void wldat_get_sizes_impl_(const char *file_path, int *size) {

    /* Get dimensions */
    int dimensions = wldat_get_dimensions_impl_(file_path);

    /* Initialize counts */
    for (int i = 0; i < dimensions; i++) {
        size[i] = 1;
    }

    /* Open file */
    FILE *file = fopen(file_path, "r");
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
            
            size[dimensions - active_dimensions - 1]++;
        }
    }

    /* Close file */
    fclose(file);
}

/*
    Compute flat index in row-major order. Example, considering an array
    arr of two dimensions 0<=i<IMAX and 0<=j<JMAX, in the
    row-major order one can write arr[j + JMAX*i], with the size of arr
    being IMAX*JMAX.

    Parameters:
    - indices, array with the indices i.
    - size, array with the maximum value XMAX for each x.
    - dimensions, number of x's.
*/
static inline int row_major_flat_index_impl_(const int *indices,
    const int *size, int dimensions) {
    
    int idx = 0;
    for (int d = 0; d < dimensions; d++) {
        idx = indices[d] + size[d] * idx;
    }
    return idx;
}

/*
    Implementation for a recursive function for dealing with nested braces
    from a Wolfram Language package source format with real numbers.

    Parameters:
    - file, file with the data, already read until the first '\n'.
    - level, level of the nested brace.
    - dimensions, number of dimensions of the data.
    - size, array with the size of each dimension.
    - indices, array with the indices of each dimension.
    - data, array to store the results.
*/
static inline void read_nested_braces_impl_(FILE *file, int level,
    int dimensions, const int *size, int *indices, double *data) {
    
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
            read_nested_braces_impl_(file, level + 1, dimensions, size,
                indices, data);
            element_count++;
        }
        else if (ch == '}') {
            if (buf_i > 0) {
                buf[buf_i] = '\0';
                indices[level] = element_count;
                int idx = row_major_flat_index_impl_(indices, size,
                    dimensions);
                data[idx] = parse_real_impl_(buf);
                buf_i = 0;
                element_count++;
            }
            break;
        }
        else if (ch == ',') {
            if (buf_i > 0) {
                buf[buf_i] = '\0';
                indices[level] = element_count;
                int idx = row_major_flat_index_impl_(indices, size,
                    dimensions);
                data[idx] = parse_real_impl_(buf);
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
    from a Wolfram Language package source format with complex numbers.

    Parameters:
    - file, file with the data, already read until the first '\n'.
    - level, level of the nested brace.
    - dimensions, number of dimensions of the data.
    - size, array with the size of each dimension.
    - indices, array with the indices of each dimension.
    - data, array to store the results.
*/
static inline void read_nested_braces_cplx_impl_(FILE *file, int level,
    int dimensions, const int *size, int *indices,
    tpdfcplx_impl_ *data) {
    
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
                size, indices, data);
            element_count++;
        }
        else if (ch == '}') {
            if (buf_i > 0) {
                buf[buf_i] = '\0';
                indices[level] = element_count;
                int idx = row_major_flat_index_impl_(indices, size,
                    dimensions);
                data[idx] = parse_complex_impl_(buf);
                buf_i = 0;
                element_count++;
            }
            break;
        }
        else if (ch == ',') {
            if (buf_i > 0) {
                buf[buf_i] = '\0';
                indices[level] = element_count;
                int idx = row_major_flat_index_impl_(indices, size,
                    dimensions);
                data[idx] = parse_complex_impl_(buf);
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
    Implementation for importing data of real numbers from a Wolfram Language
    package source format, and storing in an one-dimensional
    double-type array following the row-major order.

    Parameters:
    - file_path, path to the data file.
    - data, array of double-type of size S1*S2*...*SN to
    output the values following the row-major order, where N is the number of
    dimensions, and for each dimension n, being 1<=n<=N, Sn is its respective
    size. Notice that N<=128 and may be obtained through
    wldat_get_dimensions_impl_(), and Sn through wldat_get_sizes_impl_().
*/
static inline void wldat_import_impl_(const char *file_path,
    double *data) {
    
    /* Get dimensions and sizes */
    int dimensions = wldat_get_dimensions_impl_(file_path);
    int size[128];
    wldat_get_sizes_impl_(file_path, size);

    /* Open file */
    FILE *file = fopen(file_path, "r");
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
    read_nested_braces_impl_(file, 0, dimensions, size, indices,
        data);

    /* Close file */
    fclose(file);
}

/*
    Implementation for importing data of complex numbers from a Wolfram
    Language package source format, and storing in an one-dimensional
    'double complex'-type array following the row-major order.

    Parameters:
    - file_path, path to the data file.
    - data, array of 'double complex'-type of size S1*S2*...*SN to
    output the values following the row-major order, where N is the number of
    dimensions, and for each dimension n, being 1<=n<=N, Sn is its respective
    size. Notice that N<=128 and may be obtained through
    wldat_get_dimensions_impl_(), and Sn through wldat_get_sizes_impl_().
*/
static inline void wldat_import_cplx_impl_(const char *file_path,
    tpdfcplx_impl_ *data) {
    
    /* Get dimensions and sizes */
    int dimensions = wldat_get_dimensions_impl_(file_path);
    int size[128];
    wldat_get_sizes_impl_(file_path, size);

    /* Open file */
    FILE *file = fopen(file_path, "r");
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
    read_nested_braces_cplx_impl_(file, 0, dimensions, size, indices,
        data);

    /* Close file */
    fclose(file);
}

/*
    Implementation for a recursive function for writing nested braces
    from a Wolfram Language package source format with real numbers.

    Parameters:
    - file, file with the data, already read until the first '\n'.
    - level, level of the nested brace.
    - dimensions, number of dimensions of the data.
    - size, array with the size of each dimension.
    - indices, array with the indices of each dimension.
    - data, array to store the results.
*/
static inline void write_nested_braces_impl_(FILE *file, int level,
    int dimensions, const int *size, int *indices,
    const double *data) {

    fprintf(file, "{");
    for (int i = 0; i < size[level]; i++) {
        indices[level] = i;
        if (level == dimensions - 1) {
            /* Deepest level -> print number */
            int idx = row_major_flat_index_impl_(indices, size,
                dimensions);
            char buf[128];
            e_to_star_caret_impl_(buf, sizeof(buf), data[idx]);
            fprintf(file, "%s", buf);
        }
        else {
            /* Recurse into next level */
            write_nested_braces_impl_(file, level + 1, dimensions,
                size, indices, data);
        }
        if (i < size[level] - 1) fprintf(file, ", ");
    }
    fprintf(file, "}");
}

/*
    Implementation for a recursive function for writing nested braces
    from a Wolfram Language package source format with complex numbers.

    Parameters:
    - file, file with the data, already read until the first '\n'.
    - level, level of the nested brace.
    - dimensions, number of dimensions of the data.
    - size, array with the size of each dimension.
    - indices, array with the indices of each dimension.
    - data, array to store the results.
*/
static inline void write_nested_braces_cplx_impl_(FILE *file, int level,
    int dimensions, const int *size, int *indices,
    const tpdfcplx_impl_ *data) {

    fprintf(file, "{");
    for (int i = 0; i < size[level]; i++) {
        indices[level] = i;
        if (level == dimensions - 1) {
            /* Deepest level -> print number */
            int idx = row_major_flat_index_impl_(indices, size,
                dimensions);
            char buf_re[128], buf_abs_im[128];
            e_to_star_caret_impl_(buf_re, sizeof(buf_re),
                creal(data[idx]));
            e_to_star_caret_impl_(buf_abs_im, sizeof(buf_abs_im),
                fabs(cimag(data[idx])));
            if (cimag(data[idx]) < 0.0) {
                fprintf(file, "%s - %s*I", buf_re, buf_abs_im);
            }
            else {
                fprintf(file, "%s + %s*I", buf_re, buf_abs_im);
            }
        }
        else {
            /* Recurse into next level */
            write_nested_braces_cplx_impl_(file, level + 1, dimensions,
                size, indices, data);
        }
        if (i < size[level] - 1) fprintf(file, ", ");
    }
    fprintf(file, "}");
}

/*
    Implementation for exporting double-type data of an one-dimensional
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
static inline void wldat_export_impl_(const char *file_path,
    const double *data, int dimensions, const int *size,
    const char *comment) {

    /* Open file */
    FILE *file = fopen(file_path, "w");
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
    write_nested_braces_impl_(file, 0, dimensions, size, indices,
        data);

    /* Break line */
    fprintf(file, "\n");

    /* Close file */
    fclose(file);
}

/*
    Implementation for exporting 'double complex'-type data of an
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
static inline void wldat_export_cplx_impl_(const char *file_path,
    const tpdfcplx_impl_ *data, int dimensions, const int *size,
    const char *comment) {

    /* Open file */
    FILE *file = fopen(file_path, "w");
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
    write_nested_braces_cplx_impl_(file, 0, dimensions, size, indices,
        data);

    /* Break line */
    fprintf(file, "\n");

    /* Close file */
    fclose(file);
}

#endif /* DATA_FILE_LIBRARY_WLDAT_IMPL_H */