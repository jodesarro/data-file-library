# Data File Library: A set of C functions for handling numeric data files

This project provides a C library
([compatible with C++](#compatibility-with-c)) designed for importing
and exporting data files containing real or complex numbers.

## Available features

### Comma-Separated Values file (.csv)

A Comma-Separated Values (CSV) file represents data in a two-dimensional
matrix, where each row is separated by a line break and each column is
separated by a comma.

<details>
  <summary>
    <code><b>csvdat_get_sizes(file_path, &rows, &columns)</b></code>
  </summary>

  - **Description:** Gets the size in each dimension (number of rows and
  columns) from a Comma-Separated Values data file.
  - **Parameters:**
    - `file_path`, path to the file.
    - `rows`, to output the number of rows.
    - `columns`, to output the number of columns.
</details>

<details>
  <summary>
    <code><b>csvdat_import(file_path, data)</b></code>
  </summary>

  - **Description:** Imports `double`-type data from a Comma-Separated Values
  data file and stores in an one-dimensional `double`-type array following the
  row-major order. The values may also be in the base 10 exponential form `eN`
  or `*^N`, where `N` is an integer.
  - **Parameters:**
    - `file_path`, path to the file.
    - `data`, one-dimensional `double`-type array of the size
    `rows*columns` to output the data following the row-major order, where
    `rows` and `columns` may be obtained through `csvdat_get_sizes()`. The
    outputted data may be accessed through `data[j + columns*i]`, where
    `i` is any row and `j` is any column.
</details>

<details>
  <summary>
    <code><b>csvdat_import_cplx(file_path, data)</b></code>
  </summary>

  - **Description:** Imports `double complex`-type data from a
  Comma-Separated Values data file
  and stores the values in an one-dimensional `double complex`-type array
  following the row-major order. The complex values may be of the type `a`,
  `a+bi`, `bi`, and `i`, where `i` may also be `j`, `*i`, `*j`, or `*I`, and
  where `a` and `b` may also be in the base 10 exponential form `eN` or `*^N`,
  where `N` is an integer.
  - **Parameters:**
    - `file_path`, path to the file.
    - `data`, one-dimensional `double complex`-type array of the size
    `rows*columns` to output the data following the row-major order, where
    `rows` and `columns` may be obtained through `csvdat_get_sizes()`.
    The outputted data may be accessed through `data[j + columns*i]`,
    where `i` is any row and `j` is any column.
</details>

<details>
  <summary>
    <code><b>csvdat_export(file_path, data, rows, columns) </b></code>
  </summary>

  - **Description:** Exports `double`-type data of an one-dimensional
    `double`-type array, following the row-major order, to a Comma-Separated
    Values data file.
  - **Parameters:**
    - `file_path`, path to the file.
    - `data`, one-dimensional `double`-type array of the size
    `rows*columns` containing the data. The data is accessed following the
    row-major order, i.e., through `data[j + columns*i]`, where `i` is
    any row and `j` is any column.
    - `rows`, number of rows of the data.
    - `columns`, number of columns of the data.
</details>

<details>
  <summary>
    <code><b>csvdat_export_cplx(file_path, data, rows, columns)</b></code>
  </summary>

  - **Description:** Exports `double complex`-type data of an
    one-dimensional `double complex`-type array,
    following the row-major
    order, to a Comma-Separated Values data file.
    The exported complex values are of the type `a+bi`.
  - **Parameters:**
    - `file_path`, path to the file.
    - `data`, one-dimensional `double complex`-type array of the size
    `rows*columns` containing the data. The data is accessed following the
    row-major order, i.e., through `data[j + columns*i]`, where `i` is
    any row and `j` is any column.
    - `rows`, number of rows of the data.
    - `columns`, number of columns of the data.
</details>

### Tab-Separated Values file (.tsv)

A Tab-Separated Values (TSV) file represents data in a two-dimensional
matrix, where each row is separated by a line break and each column is
separated by a tabular spacing.

<details>
  <summary>
    <code><b>tsvdat_get_sizes(file_path, &rows, &columns)</b></code>
  </summary>

  - **Description:** Gets the size in each dimension (number of rows and
  columns) from a Tab-Separated data file.
  - **Parameters:**
    - `file_path`, path to the file.
    - `rows`, to output the number of rows.
    - `columns`, to output the number of columns.
</details>

<details>
  <summary>
    <code><b>tsvdat_import(file_path, data)</b></code>
  </summary>

  - **Description:** Imports `double`-type data from a Tab-Separated Values
  data file and stores in an one-dimensional `double`-type array following the
  row-major order. The values may also be in the base 10 exponential form `eN`
  or `*^N`, where `N` is an integer.
  - **Parameters:**
    - `file_path`, path to the file.
    - `data`, one-dimensional `double`-type array of the size
    `rows*columns` to output the data following the row-major order, where
    `rows` and `columns` may be obtained through `tsvdat_get_sizes()`. The
    outputted data may be accessed through `data[j + columns*i]`, where
    `i` is any row and `j` is any column.
</details>

<details>
  <summary>
    <code><b>tsvdat_import_cplx(file_path, data)</b></code>
  </summary>

  - **Description:** Imports `double complex`-type data from a
  Tab-Separated Values data file
  and stores the values in an one-dimensional `double complex`-type array
  following the row-major order. The complex values may be of the type `a`,
  `a+bi`, `bi`, and `i`, where `i` may also be `j`, `*i`, `*j`, or `*I`, and
  where `a` and `b` may also be in the base 10 exponential form `eN` or `*^N`,
  where `N` is an integer.
  - **Parameters:**
    - `file_path`, path to the file.
    - `data`, one-dimensional `double complex`-type array of the size
    `rows*columns` to output the data following the row-major order, where
    `rows` and `columns` may be obtained through `tsvdat_get_sizes()`.
    The outputted data may be accessed through `data[j + columns*i]`,
    where `i` is any row and `j` is any column.
</details>

<details>
  <summary>
    <code><b>tsvdat_export(file_path, data, rows, columns)</b></code>
  </summary>

  - **Description:** Exports `double`-type data of an one-dimensional
    `double`-type array, following the row-major order, to a Tab-Separated
    Values data file.
  - **Parameters:**
    - `file_path`, path to the file.
    - `data`, one-dimensional `double`-type array of the size
    `rows*columns` containing the data. The data is accessed following the
    row-major order, i.e., through `data[j + columns*i]`, where `i` is
    any row and `j` is any column.
    - `rows`, number of rows of the data.
    - `columns`, number of columns of the data.
</details>

<details>
  <summary>
    <code><b>tsvdat_export_cplx(file_path, data, rows, columns)</b></code>
  </summary>

  - **Description:** Exports `double complex`-type data of an
    one-dimensional `double complex`-type array,
    following the row-major
    order, to a Tab-Separated Values data file.
    The exported complex values are of the type `a+bi`.
  - **Parameters:**
    - `file_path`, path to the file.
    - `data`, one-dimensional `double complex`-type array of the size
    `rows*columns` containing the data. The data is accessed following the
    row-major order, i.e., through `data[j + columns*i]`, where `i` is
    any row and `j` is any column.
    - `rows`, number of rows of the data.
    - `columns`, number of columns of the data.
</details>

### Wolfram Language package source format (.wl)

A [Wolfram Language package source format (WL)](https://reference.wolfram.com/language/ref/format/WL.html)
represents data of an arbitrary dimensional matrix in a structure where
the values are separated by commas and arrays are grouped by braces, i.e.,
nested braces structures usually called
[lists](https://reference.wolfram.com/language/tutorial/Lists.html).
Such format is very useful for importing and exporting
tensors, matrices, tables, numeric datasets and so on.

<details>
  <summary>
    <code><b>wldat_get_comment_size(file_path)</b></code>
  </summary>

  - **Description:** Returns the size of the comment from a Wolfram
  Language package source format, i.e., the number of characters of the
  first line of the file plus a `'\0'` char.
  - **Parameter:**
    - `file_path`, path to the file.
</details>

<details>
  <summary>
    <code><b>wldat_get_comment(file_path, comment)</b></code>
  </summary>

  - **Description:** Gets the comment from a Wolfram Language package
  source format, i.e., the text of the whole first line of the file plus
  a `'\0'` char.
  - **Parameters:**
    - `file_path`, path to the file.
    - `comment`, array of size given by `wldat_get_comment_size()`, to
    output the text.
</details>

<details>
  <summary>
    <code><b>wldat_get_dimensions(file_path)</b></code>
  </summary>

  - **Description:** Returns the number of dimensions from a Wolfram
  Language package source format.
  The number of dimensions is limited to `128`.
  - **Parameter:**
    - `file_path`, path to the file.
</details>

<details>
  <summary>
    <code><b>wldat_get_sizes(file_path, size)</b></code>
  </summary>

  - **Description:** Gets the size of each dimension from a Wolfram
  Language package source format.
  - **Parameters:**
    - `file_path`, path to the file.
    - `size`, array of size given by `wldat_get_dimensions()`, to
    sequentially output the size of each dimension. The size of this array
    is limited to `128`.
</details>

<details>
  <summary>
    <code><b>wldat_import(file_path, data)</b></code>
  </summary>

  - **Description:** Imports data of real numbers from a Wolfram Language
  package source format, and stores in an one-dimensional
  `double`-type array following the row-major order.
  - **Parameters:**
    - `file_path`, path to the data file.
    - `data`, array of double-type of size `S1*S2*...*SN` to
    output the values following the row-major order, where `N` is the number
    of dimensions, and for each dimension `n`, being `1<=n<=N`, `Sn` is its
    respective size. Notice that `N<=128` and may be obtained through
    `wldat_get_dimensions()`, and `Sn` through `wldat_get_sizes()`.
</details>

<details>
  <summary>
    <code><b>wldat_import_cplx(file_path, data)</b></code>
  </summary>

  - **Description:** Imports data of complex numbers from a Wolfram
  Language package source format, and stores in an one-dimensional
  `double complex`-type array following the row-major order.
  - **Parameters:**
    - `file_path`, path to the data file.
    - `data`, array of `double complex`-type of size `S1*S2*...*SN` to
    output the values following the row-major order, where `N` is the number
    of dimensions, and for each dimension `n`, being `1<=n<=N`, `Sn` is its
    respective size. Notice that `N<=128` and may be obtained through
    `wldat_get_dimensions()`, and `Sn` through `wldat_get_sizes()`.
</details>

<details>
  <summary>
    <code><b>wldat_export(file_path, data, dimensions, size, comment)</b></code>
  </summary>

  - **Description:** Exports `double`-type data of an one-dimensional
    `double`-type array, following the row-major order, to Wolfram Language
    package source format of arbitrary dimension.

  - **Parameters:**
    - `file_path`, path to the data file.
    - `data`, array of double-type of size `S1*S2*...*SN`, containing
    data following the row-major order, where `N` is the number of dimensions,
    and for each dimension `n`, being `1<=n<=N`, `Sn` is its respective size.
    - `dimensions`, number `N` of the dimensions of the data, limited to
    `128`.
    - `size`, array of size `N` containing the size of each dimension.
    - `comment`, text to be stored at the very first line of the file.
</details>

<details>
  <summary>
    <code><b>wldat_export_cplx(file_path, data, dimensions, size, comment)</b></code>
  </summary>

  - **Description:** Exports `double complex`-type data of an
    one-dimensional `double complex`-type array, following the row-major
    order, to Wolfram Language package source format of arbitrary dimension.

  - **Parameters:**
    - `file_path`, path to the data file.
    - `data`, array of `double complex`-type of size `S1*S2*...*SN`,
    containing data following the row-major order, where `N` is the number of
    dimensions, and for each dimension `n`, being `1<=n<=N`, `Sn` is its
    respective size.
    - `dimensions`, number `N` of the dimensions of the data, limited to
    `128`.
    - `size`, array of size `N` containing the size of each dimension.
    - `comment`, text to be stored at the very first line of the file.
</details>

## How to use

This library is in a header-only style, i.e., there is nothing to build
(see the section [Compiling the library](#compiling-the-library) if you still
want to compile it).
Therefore, you only need to paste all the content of the
[include](include/) folder
inside the include folder of your project (if you do not have an include
folder in your project, paste the content inside the root folder of your
project). Finally, just write `#include "data-file-library.h"` at the very
beginning of your code and you shall be ready to use the functions.

<details>
  <summary>
    <b>Example of usage for CSV files in C/C++</b>
  </summary><br/>

**CSV file with complex numbers and previously known sizes**

```c
#include <complex.h> /* C++ users must include <complex> instead */
#include "data-file-library.h" /* The library */

int main() {

    /* Size of each dimension */
    int rows = 15; /* Number of rows */
    int columns = 15; /* Number of columns */

    /* Array to store the data (complex numbers) */
    /* C++ users must replace 'double complex' type by std::complex<double> */
    double complex data[rows*columns];

    /* Import the data (complex numbers) */
    csvdat_import_cplx("myfile.csv", data);

    /*
        The data at any row r and column c, may be acessed through
        data[c + columns*r]
    */
    
    /* Export the data (complex numbers) */
    csvdat_export_cplx("myfile2.csv", data, rows, columns);

    return 0;
}
```

**CSV file with complex numbers and unknown sizes**

```c
#include <stdlib.h> /* For malloc() and free() */
#include <complex.h> /* C++ users must include <complex> instead */
#include "data-file-library.h" /* The library */

int main() {

    /* Unknown size of each dimension */
    int rows; /* Number of rows */
    int columns; /* Number of columns */

    /* Get the sizes */
    csvdat_get_sizes("myfile.csv", &rows, &columns);

    /* Array to store the data (complex numbers) */
    /* C++ users must replace 'double complex' type by std::complex<double> */
    double complex *data = (int *)malloc(rows*columns * sizeof(int));

    /* Import the data (complex numbers) */
    csvdat_import_cplx("myfile.csv", data);

    /*
        The data at any row r and column c, may be acessed through
        data[c + columns*r]
    */
    
    /* Export the data (complex numbers) */
    csvdat_export_cplx("myfile2.csv", data, rows, columns);

    /* Free allocated memory */
    free(data);

    return 0;
}
```
</details>

<details>
  <summary>
    <b>Example of usage for TSV files in C/C++</b>
  </summary><br/>

**TSV file with complex numbers and previously known sizes**

```c
#include <complex.h> /* C++ users must include <complex> instead */
#include "data-file-library.h" /* The library */

int main() {

    /* Size of each dimension */
    int rows = 15; /* Number of rows */
    int columns = 15; /* Number of columns */

    /* Array to store the data (complex numbers) */
    /* C++ users must replace 'double complex' type by std::complex<double> */
    double complex data[rows*columns];

    /* Import the data (complex numbers) */
    tsvdat_import_cplx("myfile.tsv", data);

    /*
        The data at any row r and column c, may be acessed through
        data[c + columns*r]
    */
    
    /* Export the data (complex numbers) */
    tsvdat_export_cplx("myfile2.tsv", data, rows, columns);

    return 0;
}
```

**TSV file with complex numbers and unknown sizes**

```c
#include <stdlib.h> /* For malloc() and free() */
#include <complex.h> /* C++ users must include <complex> instead */
#include "data-file-library.h" /* The library */

int main() {

    /* Unknown size of each dimension */
    int rows; /* Number of rows */
    int columns; /* Number of columns */

    /* Get the sizes */
    tsvdat_get_sizes("myfile.tsv", &rows, &columns);

    /* Array to store the data (complex numbers) */
    /* C++ users must replace 'double complex' type by std::complex<double> */
    double complex *data = (int *)malloc(rows*columns * sizeof(int));

    /* Import the data (complex numbers) */
    tsvdat_import_cplx("myfile.tsv", data);

    /*
        The data at any row r and column c, may be acessed through
        data[c + columns*r]
    */
    
    /* Export the data (complex numbers) */
    tsvdat_export_cplx("myfile2.tsv", data, rows, columns);

    /* Free allocated memory */
    free(data);

    return 0;
}
```
</details>

<details>
  <summary>
    <b>Example of usage for WL files in C/C++</b>
  </summary><br/>

**WL file with complex numbers and previously known dimensions and sizes**

```c
#include <complex.h> /* C++ users must include <complex> instead */
#include "data-file-library.h" /* The library */

int main() {

    /* Number of dimensions */
    int dimensions = 3; /* Assuming a 3D matrix, dimensions in i, j, and k */

    /* Size of each dimension */
    int imax = 15; /* Size of the dimension i */
    int jmax = 15; /* Size of the dimension j */
    int kmax = 15; /* Size of the dimension k */

    /* Array to store the data (complex numbers) */
    /* C++ users must replace 'double complex' type by std::complex<double> */
    double complex data[imax*jmax*kmax];

    /* Import the data (complex numbers) */
    wldat_import_cplx("myfile.wl", data);

    /*
        The data at positions i, j, and k, may be acessed through
        data[k + kmax*j + kmax*jmax*i]
    */
    
    /* Export the data (complex numbers) */
    int size[dimensions] = {imax, jmax, kmax};
    wldat_export_cplx("myfile2.wl", data, dimensions, size, "");

    return 0;
}
```

**WL file with complex numbers and unknown dimensions and sizes**

```c
#include <stdlib.h> /* For malloc() and free() */
#include <complex.h> /* C++ users must include <complex> instead */
#include "data-file-library.h" /* The library */

int main() {

    /* Get the number of dimensions of the WL file */
    int dimensions = wldat_get_dimensions("myfile.wl");

    /* Get the size of each dimension of the WL file */
    int *size = (int *)malloc(dimensions * sizeof(int));
    wldat_get_sizes("myfile.wl", size);

    /* Get the total size (size[0] * size[1] * ... * size[dimensions-1]) */
    int totalsize = 1;
    for (int i = 0; i<dimensions; i++) {
        totalsize *= size[i];
    }

    /* Array to store the data (complex numbers) */
    /* C++ users must replace 'double complex' type by std::complex<double> */
    double complex *data = (int *)malloc(totalsize * sizeof(int));

    /* Import the data (complex numbers) */
    wldat_import_cplx("myfile.wl", data);

    /*
        As an example, for a 3D matrix, dimensions = 3,
        the data at positions i, j, and k may be acessed through
        data[k + kmax*j + kmax*jmax*i]
        where imax = size[0], jmax = size[1], and kmax = size[2],
        and so 0<=i<imax, 0<=j<jmax and 0<=k<kmax.
    */
    
    /* Export the data (complex numbers) */
    wldat_export_cplx("myfile2.wl", data, dimensions, size, "");

    /* Free allocated memories */
    free(size);
    free(data);

    return 0;
}
```
</details>

## Some C details

All routines in this library follow the row‑major order convention for
storing multi‑dimensional arrays in one‑dimensional (linear) arrays,
a method widely used in C programming.

Moreover, the implementation adheres to the C99 standard, and all complex
variables are represented using the `double complex` type provided by the
C `<complex.h>` library.

Notice that functions, macros, constants, and files whose names contain the
suffix `_impl_` are internal components and are not intended for direct use
by end users.

## Compatibility with C++

This library uses `__cplusplus` compiler guards with `extern "C"` and
macros to ensure C++ compatibility (C++98 standard at least).

In this sense, when using C++ compilers, the following C functions are
automatically mapped to their C++ equivalent: `creal(z)`↦`std::real(z)`,
`cimag(z)`↦`std::imag(z)`; and all complex values are handled
by means of the `std::complex<double>` type of the C++ `<complex>` library.

## Compiling the library

As aforementioned, usually it is not necessary to compile the library.
However, in any case, the [src](src/) folder contains the files
[data-file-library-declarations.c](src/data-file-library-declarations.c) and
[data-file-library-declarations.cpp](src/data-file-library-declarations.cpp), with
declarations of all functions in respectively C and C++, and the file
[data-file-library.c](src/data-file-library.c), which is a C wrapper
([compatible with C++](#compatibility-with-c)) that may be used for
compilation.

The following are examples of how to compile this library using C and C++
compilers.

<details>
  <summary>
    <b>Compiling on Windows with MinGW gcc</b>
  </summary>

  ```bash
  gcc -shared -o src/data-file-library.dll src/data-file-library.c -Iinclude
  ```
</details>

<details>
  <summary>
    <b>Compiling on Windows with MinGW g++</b>
  </summary>

  ```bash
  g++ -shared -o src/data-file-library.dll src/data-file-library.c -Iinclude
  ```
</details>

<details>
  <summary>
    <b>Compiling on Linux/macOS with gcc</b>
  </summary>

  ```bash
  gcc -shared -fPIC -o src/data-file-library.so src/data-file-library.c -Iinclude
  ```
</details>

<details>
  <summary>
    <b>Compiling on Linux/macOS with g++</b>
  </summary>

  ```bash
  g++ -shared -fPIC -o src/data-file-library.so src/data-file-library.c -Iinclude
  ```
</details>

<details>
  <summary>
    <b>Compiling on Windows with MSVC cl</b>
  </summary> 

  Compiling this library with MSVC targeting the C language is discouraged
  because MSVC does not support the `double complex` type from the C
  `<complex.h>` library. However, you may build it in MSVC
  targeting the C++ language (e.g., using the `/TP` flag).

  ```bash
  cl /TP src/data-file-library.c
  ```
</details>

## Other programming languages

Once compiled, it is also possible to use this library together with other
programming languages.

The following is an example on how to load the compiled library in Python
using `numpy` and `cffi`.

<details>
  <summary>
    <b>Example of usage in Python</b>
  </summary>

```python
import numpy as np
from cffi import FFI

ffi = FFI()

# Read the functions declarations
with open("src/data-file-library-declarations.c", "r") as f: # if C compiled
# with open("src/data-file-library-declarations.cpp", "r") as f: # if C++ compiled
    ffi.cdef(f.read())

# Import the compiled file
lib = ffi.dlopen("src/data-file-library.so") # for Linux/macOS
# lib = ffi.dlopen("src/data-file-library.dll") # for Windows

# Prepare a NumPy array of complex128 (matches C double complex)
n = 100  # total size of the one dimensional array you expect
arr = np.empty(n, dtype=np.complex128)

# Get a pointer to the array’s data
c_arr = ffi.cast("double complex *", arr.ctypes.data)

# Call the function
lib.wldat_import_cplx(b"myfile.wl", c_arr)

# Now arr is filled by the C function. Print the array.
print(arr)
```
</details>

## Change log

Refer to the [CHANGELOG.md](CHANGELOG.md) file for the latest updates.

## Authorship

The codes and routines were developed and are updated by
<a href="https://www.researchgate.net/profile/Jhonas-de-Sarro">
Jhonas O. de Sarro</a> ([@jodesarro](https://github.com/jodesarro)).

## Licensing

This project is protected under [MIT License](LICENSE). A copy of the license
is available at
[include/data-file-library/license.txt](include/data-file-library/license.txt).