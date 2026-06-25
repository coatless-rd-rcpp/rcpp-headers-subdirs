# Using Both Subdirectory Functions

These function serve as intermediaries between R and the subdirectory
source.

## Usage

``` r
calc_modifications(x)

calc_A_export(x)

calc_B_export(x)
```

## Arguments

- x:

  Vector of Numeric Values with length \\n\\.

## Value

A vector of numeric values with length \\n\\.

## Details

The exported function name is different from the subdirectory function.
C++ does not allow duplicate function names with the same parameters. To
preserve the original function name necessitates the subdirectory
function being placed behind a namespace, e.g. \`A::calc_A_routine()\`.
Otherwise, the name of the function exported must be different, e.g.
\`calc_A_export()\`.

## Examples

``` r
my_vec = c(3.5, 8, -1.5, -2, 0, 42)
calc_modifications(my_vec)
#> [1]  5 14 -5 -6 -2 82
my_vecA = c(881, 884, 1,2,-4)
calc_A_export(my_vec)
#> [1] -0.5  4.0 -5.5 -6.0 -4.0 38.0
my_vecB = c(512,32, -1, 1.3, 5.9)
calc_B_export(my_vecB)
#> [1] 514.0  34.0   1.0   3.3   7.9
```
