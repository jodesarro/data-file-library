# Data File Library: A set of C functions for handling numeric data files

This project provides a C library
([fully compatible with C++](#compatibility-with-c)) designed for importing
and exporting data files with real or complex numbers.

## Available features

### Comma-Separated Values file (.csv)

A Comma-Separated Values (CSV) file represents data in a two-dimensional
matrix, where each row is separated by a line break and each column is
separated by a comma.

<details>
  <summary>
    <code><b>csvdat_get_sizes(csvdat_path, rows, columns)</b></code>
  </summary>

  - **Description:** Gets the size in each dimension (number of rows and
  columns) of a Comma-Separated Values data file.
  - **Parameters:**
    - `csvdat_path`, path to the file.
    - `&rows`, for storing the number of rows.
    - `&columns`, for storing the number of columns.
</details>

<details>
  <summary>
    <code><b>csvdat_import(csvdat_path, data_array)</b></code>
  </summary>

  - **Description:** Imports double-type data from a Comma-Separated Values
  data file and store the values in an one-dimensional double-type array. The
  values may also be in the base 10 exponential form `eN` or `*^N`, where `N`
  is an integer.
  - **Parameters:**
    - `csvdat_path`, path to the file.
    - `data_array`, one-dimensional double-type array of the size
    `rows*columns` for storing the data. The array must have `rows*columns`
    size, where rows and columns may be obtained through `csvdat_get_sizes()`.
    Its data may be accessed through `data_array[i + rows*j]`, where `i` is
    any row and `j` is any column.
</details>

<details>
  <summary>
    <code><b>csvdat_import_cplx(csvdat_path, data_array)</b></code>
  </summary>

  - **Description:** Imports complex-type data from a Comma-Separated Values
    data file and store the values in an one-dimensional complex-type array.
    The complex values may be of the type `a`, `a+bi`, `bi`, `i`, and `-i`,
    where `i` may also be `j`, `*i`, `*j`, or `*I`, and where `a` and `b` may
    also be in the base 10 exponential form `eN` or `*^N`, where `N` is an
    integer.
  - **Parameters:**
    - `csvdat_path`, path to the file.
    - `data_array`, one-dimensional complex-type array of the size
    `rows*columns` for storing the data. The array must have `rows*columns`
    size, where `rows` and `columns` may be obtained through
    `csvdat_get_sizes()`. Its data may be accessed through
    `data_array[i + rows*j]`, where `i` is any row and `j` is any column.
</details>

<details>
  <summary>
    <code><b>csvdat_export(csvdat_path, data_array, rows, columns) </b></code>
  </summary>

  - **Description:** Exports double-type data of an one-dimensional
  double-type array to a Comma-Separated Values data file.
  - **Parameters:**
    - `csvdat_path`, path to the file.
    - `data_array`, one-dimensional double-type array of the size
    `rows*columns` containing the data. The data is accessed through
    `data_array[i + rows*j]`, where `i` is a row and `j` is a column.
    - `rows`, number of rows of the data.
    - `columns`, number of columns of the data.
</details>

<details>
  <summary>
    <code><b>csvdat_export_cplx(csvdat_path, data_array, rows, columns)</b></code>
  </summary>

  - **Description:** Exports complex-type data of an one-dimensional
  complex-type array to a Comma-Separated Values data file. The exported
  complex values are of the type `a+bi`.
  - **Parameters:**
    - `csvdat_path`, path to the file.
    - `data_array`, one-dimensional complex-type array of the size
    `rows*columns` containing the data. The data is accessed through
    `data_array[i + rows*j]`, where `i` is a row and `j` is a column.
    - `rows`, number of rows of the data.
    - `columns`, number of columns of the data.
</details>

### Tab-Separated Values file (.tsv)

A Tab-Separated Values (TSV) file represents data in a two-dimensional
matrix, where each row is separated by a line break and each column is
separated by a tabular spacing.

<details>
  <summary>
    <code><b>tsvdat_get_sizes(tsvdat_path, rows, columns)</b></code>
  </summary>

  - **Description:** Gets the size in each dimension (number of rows and
  columns) of a Tab-Separated data file.
  - **Parameters:**
    - `tsvdat_path`, path to the file.
    - `&rows`, for storing the number of rows.
    - `&columns`, for storing the number of columns.
</details>

<details>
  <summary>
    <code><b>tsvdat_import(tsvdat_path, data_array)</b></code>
  </summary>

  - **Description:** Imports double-type data from a Tab-Separated data file
  and store the values in an one-dimensional double-type array. The values may
  also be in the base 10 exponential form `eN` or `*^N`, where `N` is an
  integer.
  - **Parameters:**
    - `tsvdat_path`, path to the file.
    - `data_array`, one-dimensional double-type array of the size
    `rows*columns` for storing the data. The array must have `rows*columns`
    size, where `rows` and columns may be obtained through
    `tsvdat_get_sizes()`. Its data may be accessed through
    `data_array[i + rows*j]`, where `i` is any row and `j` is any column.
</details>

<details>
  <summary>
    <code><b>tsvdat_import_cplx(tsvdat_path, data_array)</b></code>
  </summary>

  - **Description:** Imports complex-type data from a Tab-Separated data file
  and store the values in an one-dimensional complex-type array. The complex
  values may be of the type `a`, `a+bi`, `bi`, `i`, and `-i`, where `i` may
  also be `j`, `*i`, `*j`, or `*I`, and where `a` and `b` may also be in the
  base 10 exponential form `eN` or `*^N`, where `N` is an integer.
  - **Parameters:**
    - `tsvdat_path`, path to the file.
    - `data_array`, one-dimensional complex-type array of the size
    `rows*columns` for storing the data. The array must have `rows*columns`
    size, where `rows` and `columns` may be obtained through
    `tsvdat_get_sizes()`. Its data may be accessed through
    `data_array[i + rows*j]`, where `i` is any row and `j` is any column.
</details>

<details>
  <summary>
    <code><b>tsvdat_export(tsvdat_path, data_array, rows, columns)</b></code>
  </summary>

  - **Description:** Exports double-type data of an one-dimensional
  double-type array to a Tab-Separated data file.
  - **Parameters:**
    - `tsvdat_path`, path to the file.
    - `data_array`, one-dimensional double-type array of the size
    `rows*columns` containing the data. The data is accessed through
    `data_array[i + rows*j]`, where `i` is a row and `j` is a column.
    - `rows`, number of rows of the data.
    - `columns`, number of columns of the data.
</details>

<details>
  <summary>
    <code><b>tsvdat_export_cplx(tsvdat_path, data_array, rows, columns)</b></code>
  </summary>

  - **Description:** Exports complex-type data of an one-dimensional
  complex-type array to a Tab-Separated data file. The exported complex values
  are of the type `a+bi`.
  - **Parameters:**
    - `tsvdat_path`, path to the file.
    - `data_array`, one-dimensional complex-type array of the size
    `rows*columns` containing the data. The data is accessed through
    `data_array[i + rows*j]`, where `i` is a row and `j` is a column.
    - `rows`, number of rows of the data.
    - `columns`, number of columns of the data.
</details>

### Wolfram Language package source format (.wl)

A [Wolfram Language package source format (WL)](https://reference.wolfram.com/language/ref/format/WL.html)
file represents data of an arbitrary imensional matrix in a structure where
data are separated by commas and arrays are grouped by braces, i.e., a nested
braces structure. Such format is very useful for importing and exporting
tensors, matrices, tables, numeric datasets and so on.

<details>
  <summary>
    <code><b>wldat_get_comment_size(wldat_path)</b></code>
  </summary>

  - **Description:** Returns the size of the comment of a Wolfram
  Language file format, i.e., the number of characters of the first line of
  the file plus a '\0' char.
  - **Parameters:**
    `- wldat_path`, path to the file.
</details>

<details>
  <summary>
    <code><b>wldat_get_comment(wldat_path, comment)</b></code>
  </summary>

  - **Description:** Gets the comment of a Wolfram Language file format,
  i.e., the text of the whole first line plus a '\0' char.
  - **Parameters:**
    - `wldat_path`, path to the file.
    - `comment`, array of size `wldat_get_comment_size(wldat_path)` to store
    the text.
</details>

<details>
  <summary>
    <code><b>wldat_get_dimensions(wldat_path)</b></code>
  </summary>

  - **Description:** Returns the number of dimensions of a Wolfram
  Language file format. The number of dimensions must not exceed 128.
  - **Parameters:**
    - `wldat_path`, path to the file.
</details>

<details>
  <summary>
    <code><b>wldat_get_sizes(wldat_path, sizes)</b></code>
  </summary>

  - **Description:** Gets the size of each dimension of a Wolfram Language
  file format.
  - **Parameters:**
    - `wldat_path`, path to the file.
    - `sizes`, array of size `wldat_get_dimensions(wldat_path)` to
    sequentially store the size of each dimension. The size of this array must
    not exceed 128.
</details>

<details>
  <summary>
    <code><b>wldat_import(wldat_path, data_array)</b></code>
  </summary>

  - **Description:** Imports data of real numbers of a Wolfram Language file
  format.
  - **Parameters:**
    - `wldat_path`, path to the data file.
    - `data_array`, array of size $S_1 \times S_2 \times ...\times S_N$ to
    store the results, where $N$ is the number of dimensions, and for each
    dimension $n$, where $n = 1, 2, ..., N$, $S_n$ is its size. Notice
    that $N$ may be obtained through `wldat_get_dimensions(wldat_path)` and
    $S_n$ through `wldat_get_sizes(wldat_path)`.
</details>

<details>
  <summary>
    <code><b>wldat_import_cplx(wldat_path, data_array)</b></code>
  </summary>

  - **Description:** Imports data of complex numbers of a Wolfram Language
  file format.

  - **Parameters:**
    - `wldat_path`, path to the data file.
    - `data_array`, array of size $S_1 \times S_2 \times ...\times S_N$ to
    store the results, where $N$ is the number of dimensions, and for each
    dimension $n$, where $n = 1, 2, ..., N$, $S_n$ is its size. Notice
    that $N$ may be obtained through `wldat_get_dimensions(wldat_path)` and
    $S_n$ through `wldat_get_sizes(wldat_path)`.
</details>

<details>
  <summary>
    <code><b>wldat_export(wldat_path, data_array, dimensions,sizes, comment)</b></code>
  </summary>

  - **Description:** Exports data of real numbers to a Wolfram Language file
  format.
  - **Parameters:**
    - `wldat_path`, path to the data file.
    - `data_array`, array of size $S_1 \times S_2 \times ...\times S_N$ to
    store the results, where $N$ is the number of dimensions, and for each
    dimension $n$, where $n = 1, 2, ..., N$, $S_n$ is its size.
    - `dimensions`, number of the dimensions of the data.
    - `sizes`, array with the size of each dimension.
    - `comment`, text to be stored at the very first line of the file.
</details>

<details>
  <summary>
    <code><b>wldat_export_cplx(wldat_path, data_array, dimensions,sizes, comment)</b></code>
  </summary>

  - **Description:** Exports data of complex numbers to a Wolfram Language
  file format.
  - **Parameters:**
    - `wldat_path`, path to the data file.
    - `data_array`, array of size $S_1 \times S_2 \times ...\times S_N$ to
    store the results, where $N$ is the number of dimensions, and for each
    dimension $n$, where $n = 1, 2, ..., N$, $S_n$ is its size.
    - `dimensions`, number of the dimensions of the data.
    - `sizes`, array with the size of each dimension.
    - `comment`, text to be stored at the very first line of the file.
</details>

## How to use

This library is in a header-only style, i.e., there is nothing to build
(see the section [Compiling the library](#compiling-the-library) if you still
want to compile it).
Therefore, you only need to paste all the content of the
[include folder](include/)
inside the include folder of your project (if you do not have an include
folder in your project, paste the content inside the root folder of your
project). Finally, just write `#include "data-file-library.h"` at the very
beginning of your code and you shall be ready to use the functions.

## Some C details

In this library, the implementation is carried out in terms of the C99
standards. Therefore, all the complex variables are handled using the
`double complex` type of the C `<complex.h>` library.

Notice that all functions, macros, constants and files whose names contain
the suffix `_impl_` are internal and are not intended to be used by users.

## Compatibility with C++

This library uses `__cplusplus` compiler guards with `extern "C"` and
`#define` macros to ensure C++ compatibility (C++98 standard at least).

In this sense, when using C++ compilers, the following C functions are
automatically mapped to their C++ equivalent: `creal(z)`↦`std::real(z)`,
`cimag(z)`↦`std::imag(z)`.

Moreover, all the complex variables are handled using the
`std::complex<double>` type of the C++ `<complex>` library.

## Compiling the library

As aforementioned, usually it is not necessary to compile the library.
However, in any case, the file [data-file-library.c](src/data-file-library.c)
inside the [src](src/) folder is a C wrapper that may be used for compilation.

The following are examples of how to compile this library.

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
    <b>Compiling on Linux/macOS with gcc</b>
  </summary>

  ```bash
  gcc -shared -fPIC -o src/data-file-library.so src/data-file-library.c -Iinclude
  ```
</details>

<details>
  <summary>
    <b>Compiling on Windows with MSVC cl</b>
  </summary> 

  Compiling this library with MSVC is not recommended because MSVC does not
  support the `double complex` type of the C `<complex.h>` library.
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