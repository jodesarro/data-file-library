/*
  Data File Library: A set of C functions for handling numeric data files

  Repository: <https://github.com/jodesarro/data-file-library>
  License: Refer to the LICENSE file in the Repository
  Language standard: C99 and C++98

  Description: Defines macros and typedefs for ensuring C++ compatibility
*/

#ifndef DATA_FILE_LIBRARY_CPLX_C_CPP_IMPL_H
#define DATA_FILE_LIBRARY_CPLX_C_CPP_IMPL_H

#ifdef __cplusplus

/* Includes, typedefs and/or macros for C++98 compatibility */

#include <complex>                     /* For complex numbers */
typedef std::complex<double> dcomplex; /* std::complex<double> */
#define I (dcomplex(0.0, 1.0))         /* std::complex<double>(0.0, 1.0) */
#define creal(z) (std::real(z))        /* std::real(z) */
#define cimag(z) (std::imag(z))        /* std::imag(z) */

#else

/* C99 */

#include <complex.h> /* For complex numbers */
typedef double complex dcomplex; /* double complex */

#endif /* __cplusplus */

#endif /* DATA_FILE_LIBRARY_CPLX_C_CPP_IMPL_H */