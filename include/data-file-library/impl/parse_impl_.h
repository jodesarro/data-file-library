/* 
    Data File Library: A set of C functions for handling numeric data files

    File: include/data-file-library/impl/parse_impl_.h
    Version: include/data-file-library/version.h
    Author: Jhonas Olivati de Sarro
    Language standards: C99 with guards for C++98 compatibility
    License: include/data-file-library/license.txt

    Description:
        Functions for parsing complex and real values of data files. The real
        values may also be in the base 10 exponential form eN or *^N, where N
        is an integer. The complex values may be of the type a, a+bi, bi, i,
        and -i, where i may also be j, *i, *j, or *I, and where a and b may
        also be in the base 10 exponential form eN or *^N, where N is an
        integer.
*/

#ifndef DATA_FILE_LIBRARY_PARSE_IMPL_H
#define DATA_FILE_LIBRARY_PARSE_IMPL_H

#ifdef __cplusplus

/* Includes, typedefs and/or macros for C++98 compatibility */

#include <complex> /* for complex numbers */
typedef std::complex<double> tpdcomplex_impl_;
#define I_IMPL_ std::complex<double>(0.0, 1.0)

extern "C" {

#else

#include <complex.h> /* for complex numbers */
typedef double complex tpdcomplex_impl_;
#define I_IMPL_ I

#endif /* __cplusplus */

#include <math.h> /* For NAN and INFINITY */
#include <string.h>

/*
    Removes spaces char ' ' from a string in place.
    
    Parameters:
    - str, the input string.
*/
static inline void remove_spaces_impl_(char *str) {
    int i = 0, j = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0'; /* Null-terminate the new string */
}

/*
    Removes quotes char '\"' from a string in place.
    
    Parameters:
    - str, the input string.
*/
static inline void remove_quotes_impl_(char *str) {
    int i = 0, j = 0;
    while (str[i] != '\0') {
        if (str[i] != '\"') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0'; /* Null-terminate the new string */
}

/*
    Replaces "I" by "i".
    
    Parameters:
    - str, the input string.
*/
static inline void capital_i_to_i_impl_(char *str) { 
    char *pos;
    while ((pos = strstr(str, "I")) != NULL) {
        /* Overwrite 'I' with 'i' */
        *pos = 'i';
    }
}

/*
    Replaces "j" by "i".
    
    Parameters:
    - str, the input string.
*/
static inline void j_to_i_impl_(char *str) { 
    char *pos;
    while ((pos = strstr(str, "j")) != NULL) {
        /* Overwrite 'j' with 'i' */
        *pos = 'i';
    }
}

/*
    Replaces "*i" by "i".
    
    Parameters:
    - str, the input string.
*/
static inline void star_i_to_i_impl_(char *str) { 
    char *pos;
    while ((pos = strstr(str, "*i")) != NULL) {
        /* Overwrite '*' with 'i' */
        *pos = 'i';
        /* Shift the rest of the string left by one, removing '^' */
        memmove(pos + 1, pos + 2, strlen(pos + 2) + 1);
    }
}

/*
    Replaces "*^" by "e".
    
    Parameters:
    - str, the input string.
*/
static inline void star_caret_to_e_impl_(char *str) { 
    char *pos;
    while ((pos = strstr(str, "*^")) != NULL) {
        /* Overwrite '*' with 'e' */
        *pos = 'e';
        /* Shift the rest of the string left by one, removing '^' */
        memmove(pos + 1, pos + 2, strlen(pos + 2) + 1);
    }
}

/*
    Replaces "e" by "*^".
    
    Parameters:
    - output, the output string.
    - output_size, is the sizeof(output).
    - input, the input number.
*/
static inline void e_to_star_caret_impl_(char *output, size_t output_size,
    double input) {

    char tmp[128];
    snprintf(tmp, sizeof(tmp), "%.16e", input);

    char *p = strchr(tmp, 'e');
    if (p) {
        *p = '\0';  /* Split into mantissa and exponent */
        /* Copy mantissa */
        snprintf(output, output_size, "%s", tmp);
        /* Append "*^" */
        strncat(output, "*^", output_size - strlen(output) - 1);
        /* Append exponent */
        strncat(output, p + 1, output_size - strlen(output) - 1);
    }
    else {
        snprintf(output, output_size, "%s", tmp);
    }
}

/*
    Replaces "ComplexInfinity" by "INFINITY".
    
    Parameters:
    - str, the input string.
*/
static inline void complexinfinity_to_infinity_impl_(char *str) { 
    if (strcmp(str, "ComplexInfinity") == 0) {
        strcpy(str, "INFINITY");
    }
}

/*
    Returns a real double-type value from a string. The values may also be
    in the base 10 exponential form eN or *^N, where N is an integer.
    
    Parameters:
    - str, the input numeric value.
*/
static inline double parse_real_impl_(char *str) {
    
    complexinfinity_to_infinity_impl_(str);
    remove_spaces_impl_(str);
    remove_quotes_impl_(str);
    star_caret_to_e_impl_(str);

    double real;

    if (sscanf(str, "%lf", &real) == 1) {
        return real;
    }
    else {
        return NAN;
    }
}

/*
    Returns a real 'double complex'-type value from a string considering C,
    Wolfram Language (WL), and Matlab conventions. The complex values
    may be of the type a, a+bi, bi, i, and -i, where i may also be j, *i, *j,
    or *I, and where a and b may also be in the base 10 exponential form eN
    or *^N, where N is an integer.
    
    Parameters:
    - str, the input numeric complex value.
*/
static inline tpdcomplex_impl_ parse_complex_impl_(char *str) {
    
    complexinfinity_to_infinity_impl_(str);
    remove_spaces_impl_(str);
    remove_quotes_impl_(str);
    star_caret_to_e_impl_(str);
    j_to_i_impl_(str);
    capital_i_to_i_impl_(str);
    star_i_to_i_impl_(str);

    double real, imag;
    size_t len = strlen(str);

    if (len > 0 && str[len-1] == 'i') {
        
        /* Complex number */
        if (sscanf(str, "%lf+%lfi", &real, &imag) == 2) {
            /* Complex of the type a+bi */
            return real + I_IMPL_ * imag;
        }
        else if (sscanf(str, "%lf-%lfi", &real, &imag) == 2) {
            /* Complex of the type a-bi */
            return real - I_IMPL_ * imag;
        }
        else if (sscanf(str, "%lfi", &imag) == 1) {
            /* Complex of the type bi */
            real = 0.0;
            return real + I_IMPL_ * imag;
        }
        else if (strcmp(str, "i") == 0 || strcmp(str, "+i") == 0) {
            /* Complex of the type i */
            real = 0.0; imag = 1.0;
            return real + I_IMPL_ * imag;
        }
        else if (strcmp(str, "-i") == 0) {
            /* Complex of the type -i */
            real = 0.0; imag = -1.0;
            return real + I_IMPL_ * imag;
        }
        else {
            /* Invalid complex number type */
            real = NAN; imag = NAN;
            return real + I_IMPL_ * imag;
        }
    }
    else {
        /* Real number */
        imag = 0.0;
        if (sscanf(str, "%lf", &real) == 1) {
            /* Real number of the type +a */
            return real + I_IMPL_ * imag;
        }
        else {
            /* Invalid real number type */
            real = NAN;
            return real + I_IMPL_ * imag;
        }
    }
}

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* DATA_FILE_LIBRARY_PARSE_IMPL_H */