/* 
    Data File Library: A set of C functions for handling numeric data files

    File: src/data-file-library.c
    Version: include/data-file-library/version.h
    Author: Jhonas Olivati de Sarro
    Language standards: C99
    License: include/data-file-library/license.txt

    Description:
        Wrapper for compiling the include/data-file-library.c
*/

#include <complex.h> /* for complex numbers */
typedef double complex tpdcomplex_impl_;
#include "../include/data-file-library/version.h"
#include "../include/data-file-library/impl/sepdat_impl_.h"
#include "../include/data-file-library/impl/wldat_impl_.h"

static inline void csvdat_get_sizes(const char *csvdat_path, int *rows,
    int *columns) {
    
    sepdat_get_sizes_impl_(csvdat_path, rows, columns, ',');
}

static inline void csvdat_import(const char *csvdat_path,
    double * data_array) {
    
    sepdat_import_impl_(csvdat_path, data_array, ',');
}

static inline void csvdat_import_cplx(const char *csvdat_path,
    tpdcomplex_impl_ *data_array) {
    
    sepdat_import_cplx_impl_(csvdat_path, data_array, ',');
}

static inline void csvdat_export(const char *csvdat_path,
    const double *data_array, int rows, int columns) {

    sepdat_export_impl_(csvdat_path, data_array, rows, columns, ',');
}

static inline void csvdat_export_cplx(const char *csvdat_path,
    const tpdcomplex_impl_ *data_array, int rows, int columns) {

    sepdat_export_cplx_impl_(csvdat_path, data_array, rows, columns, ',');
}

static inline void tsvdat_get_sizes(const char *tsvdat_path, int *rows,
    int *columns) {
    
    sepdat_get_sizes_impl_(tsvdat_path, rows, columns, ',');
}

static inline void tsvdat_import(const char *tsvdat_path,
    double * data_array) {
    
    sepdat_import_impl_(tsvdat_path, data_array, ',');
}

static inline void tsvdat_import_cplx(const char *tsvdat_path,
    tpdcomplex_impl_ *data_array) {
    
    sepdat_import_cplx_impl_(tsvdat_path, data_array, ',');
}

static inline void tsvdat_export(const char *tsvdat_path,
    const double *data_array, int rows, int columns) {

    sepdat_export_impl_(tsvdat_path, data_array, rows, columns, ',');
}

static inline void tsvdat_export_cplx(const char *tsvdat_path,
    const tpdcomplex_impl_ *data_array, int rows, int columns) {

    sepdat_export_cplx_impl_(tsvdat_path, data_array, rows, columns, ',');
}

static inline int wldat_get_comment_size(const char *wldat_path) {
    return wldat_get_comment_size_impl_(wldat_path);
}

static inline void wldat_get_comment(const char *wldat_path, char *comment) {
    wldat_get_comment_impl_(wldat_path, comment);
}

static inline int wldat_get_dimensions(const char *wldat_path) {
    wldat_get_dimensions_impl_(wldat_path);
}

static inline void wldat_get_sizes(const char *wldat_path, int *sizes) {
    wldat_get_sizes_impl_(wldat_path, sizes);
}

static inline void wldat_import(const char *wldat_path, double *data_array) {
    wldat_import_impl_(wldat_path, data_array);
}

static inline void wldat_import_cplx(const char *wldat_path,
    tpdcomplex_impl_ *data_array) {

    wldat_import_cplx_impl_(wldat_path, data_array); 
}

static inline void wldat_export(const char *wldat_path,
    double *data_array, int dimensions, int *sizes, char *comment) {

    wldat_export_impl_(wldat_path, data_array, dimensions, sizes, comment);
}

static inline void wldat_export_cplx(const char *wldat_path,
    tpdcomplex_impl_ *data_array, int dimensions, int *sizes, char *comment) {

    wldat_export_cplx_impl_(wldat_path, data_array, dimensions, sizes,
        comment);
}