/* 
    Bessel Library: A C library with routines for computing Bessel functions

    File: include/data-file-library/impl/cplx_c_cpp_impl_.h
    Version: include/data-file-library/version.h
    Author: Jhonas Olivati de Sarro
    Language standards: C99 and C++98 guards, macros and typedefs
    License: include/data-file-libraryy/license.txt

    Description:
        Defines macros and typedefs for ensuring C++ compatibility
*/

#ifndef DATA_FILE_LIBRARY_CPLX_C_CPP_IMPL_H
#define DATA_FILE_LIBRARY_CPLX_C_CPP_IMPL_H

#ifdef __cplusplus

/* Includes, typedefs and/or macros for C++98 compatibility */

#include <complex> /* For complex numbers */
#define I_IMPL_ std::complex<double>(0.0, 1.0)
#define creal(z) std::real(z)
#define cimag(z) std::imag(z)
typedef std::complex<double> tpdfcplx_impl_;

#else

/* C99 */

#include <complex.h> /* For complex numbers */
#define I_IMPL_ I
typedef double complex tpdfcplx_impl_;

#endif /* __cplusplus */

#endif /* DATA_FILE_LIBRARY_CPLX_C_CPP_IMPL_H */