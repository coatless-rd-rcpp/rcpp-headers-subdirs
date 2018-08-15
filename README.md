## Including C++ code in a Subdirectory within the Src Directory

[![Travis-CI Build Status](https://travis-ci.org/r-pkg-examples/rcpp-headers-subdirs.svg?branch=master)](https://travis-ci.org/r-pkg-examples/rcpp-headers-subdirs)

The `SubdirSrc` R package shows how to embed code in subdirectories within the
[`src/`](https://github.com/r-pkg-examples/rcpp-headers-subdirs/tree/master/src)
folder by modifying the [`Makevars` file](https://github.com/r-pkg-examples/rcpp-headers-subdirs/blob/master/src/Makevars), as specified in 
[Section: 1.2.1 Using Makevars](https://cran.r-project.org/doc/manuals/r-release/R-exts.html#Using-Makevars)
of [Writing R Extensions](https://cran.r-project.org/doc/manuals/r-release/R-exts.html),
which is a variant of [`Make`](https://www.gnu.org/software/make/manual/make.html) that is _unique_ to _R_.

In essence, this project shows how to go from:

```bash
src/
    |-> Makevars
    |-> Makevars.win
    |-> r-accessor-to-code.cpp
    |-> routineA.cpp
    |-> routineA.h
    |-> routineB.cpp
    |-> routineB.h
```

to: 


```bash
src/
    |-> Makevars.in
    |-> r-accessor-to-code.cpp
    |-> A
        |-> routineA.cpp
        |-> routineA.h
    |-> B
        |-> routineB.cpp
        |-> routineB.h
```

**Note: There is no way to use 
[Rcpp Attributes in subdirectories](http://lists.r-forge.r-project.org/pipermail/rcpp-devel/2015-March/008473.html).**
That is, you cannot export a function in a subdirectory of `src/` using `// [[Rcpp::export]]`. 
Thus, you would need to create and export an intermediary function in `src/`, e.g.
[`calc_modifications()`](https://github.com/r-pkg-examples/rcpp-headers-subdirs/blob/master/src/r-accessor-to-code.cpp#L22-L34)
in [`r-accessor-to-code.cpp`](https://github.com/r-pkg-examples/rcpp-headers-subdirs/blob/master/src/r-accessor-to-code.cpp). Make sure to include the headers associated with the subdirectories and that the headers have an _inclusion guard_. 

### Usage

To install the package, you must first have a compiler on your system that is 
compatible with R. For help on obtaining a compiler consult either
[macOS](http://thecoatlessprofessor.com/programming/r-compiler-tools-for-rcpp-on-os-x/)
or 
[Windows](http://thecoatlessprofessor.com/programming/rcpp/install-rtools-for-rcpp/)
guides.

With a compiler in hand, one can then install the package from GitHub by:

```r
# install.packages("devtools")
devtools::install_github("r-pkg-examples/rcpp-headers-subdirs")
library("SubdirSrc")
```

### Implementation Details

To do


## License

GPL (\>= 2)