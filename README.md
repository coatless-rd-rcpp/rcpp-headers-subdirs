## Including C++ code in a Subdirectory within the Src Directory

<!-- badges: start -->
[![R-CMD-check](https://github.com/coatless-rd-rcpp/rcpp-headers-subdirs/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/coatless-rd-rcpp/rcpp-headers-subdirs/actions/workflows/R-CMD-check.yaml)
<!-- badges: end -->

The `SubdirSrc` R package shows how to embed code in subdirectories within the
[`src/`](https://github.com/coatless-rd-rcpp/rcpp-headers-subdirs/tree/master/src)
folder by modifying the [`Makevars` file](https://github.com/coatless-rd-rcpp/rcpp-headers-subdirs/blob/master/src/Makevars), as specified in 
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
[`calc_modifications()`](https://github.com/coatless-rd-rcpp/rcpp-headers-subdirs/blob/master/src/r-accessor-to-code.cpp#L22-L34)
in [`r-accessor-to-code.cpp`](https://github.com/coatless-rd-rcpp/rcpp-headers-subdirs/blob/master/src/r-accessor-to-code.cpp). Make sure to include the headers associated with the subdirectories and that the headers have an _inclusion guard_. 

### Usage

To install the package, you must first have a compiler on your system that is 
compatible with R. For help on obtaining a compiler consult either
[macOS](http://thecoatlessprofessor.com/programming/r-compiler-tools-for-rcpp-on-os-x/)
or 
[Windows](http://thecoatlessprofessor.com/programming/rcpp/install-rtools-for-rcpp/)
guides.

With a compiler in hand, one can then install the package from GitHub by:

```r
# install.packages("remotes")
remotes::install_github("coatless-rd-rcpp/rcpp-headers-subdirs")
library("SubdirSrc")
```

### Implementation Details

To compile code in subdirectories of `src/`, each of the files contained must 
be specified in the `src/Makevars` file `OBJECTS` variable. Listing the 
individual files by hand is tedious and more prone to error if new files are 
added but not included. Dynamically retrieving files in the subdirectory and 
writing their names is preferred approach as it is more robust to such change. 

As a result, the package uses a
[`configure` file](https://github.com/coatless-rd-rcpp/rcpp-headers-subdirs/blob/master/configure)
to obtain the names of the files and write them to `src/Makevars`. 
This [`configure` file](https://github.com/coatless-rd-rcpp/rcpp-headers-subdirs/blob/master/configure) 
is generated from
[`configure.ac`](https://github.com/coatless-rd-rcpp/rcpp-headers-subdirs/blob/master/configure.ac) 
after running [`autoconf`](https://www.gnu.org/software/autoconf/autoconf.html)
once in terminal. The dynamic writing relies on the presence of a generic template,
`src/Makevars.in`, that will produce an output file, `src/Makevars` with
appropriate variables and/or paths set.

**`src/Makevars.in`** 

This file acts as the input generic template. We are seeking resolve the variable
`@SUBDIR_SOURCES@` with files found in the subdirectories of `src/`.

```bash
# Default make file
PKG_CPPFLAGS=-I.
PKG_LIBS=$(LAPACK_LIBS) $(BLAS_LIBS) $(FLIBS)

# Include all C++ files in src/ and its subdirectories: src/A and src/B 
SOURCES=r-accessor-to-code.cpp RcppExports.cpp @SUBDIR_SOURCES@
              # Variable to place contents     ^^^^^^^^^^^^^^^^

# Obtain the object files
OBJECTS=$(SOURCES:.cpp=.o) 

# Make the shared object
all: $(SHLIB)

# Provide recipe to remove all objects
clean:
	@rm -f $(OBJECTS)
```

**src/Makevars** 

This is output file created from the generic template after running the
`configure` script. Within the output file, note that the variable
`@SUBDIR_SOURCES@` has been _replaced_ with the subdirectory file paths.

```bash
# Default make file
PKG_CPPFLAGS=-I.
PKG_LIBS=$(LAPACK_LIBS) $(BLAS_LIBS) $(FLIBS)

# Include all C++ files in src/ and its subdirectories: src/A and src/B 
SOURCES=r-accessor-to-code.cpp RcppExports.cpp A/routineA.cpp B/routineB.cpp 
              # Updated with variable contents ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

# Obtain the object files
OBJECTS=$(SOURCES:.cpp=.o) 

# Make the shared object
all: $(SHLIB)

# Provide recipe to remove all objects
clean:
	@rm -f $(OBJECTS)
```

From here, any functions in the subdirectories can be used by including the
relevant header file with the function definitions. As an example,
consider [`src/A/routineA.cpp`](https://github.com/coatless-rd-rcpp/rcpp-headers-subdirs/blob/master/src/A/routineA.cpp), which stores the function implementation, and [`src/A/routineA.h`](https://github.com/coatless-rd-rcpp/rcpp-headers-subdirs/blob/master/src/A/routineA.h), which stores the function definition and incorporates an 
inclusion guard to ensure only one copy of the header file is included. 

Though, to use subdirectory functions as a traditional _R_ function, one must 
specify and export using Rcpp an intermediary function that rests in `src/`. 
An example of this can be found in [lines 36 - 53 of `src/r-accessor-to-code.cpp`](https://github.com/coatless-rd-rcpp/rcpp-headers-subdirs/blob/master/src/r-accessor-to-code.cpp#L36-L53).

### Alternative Implementation Strategies

The above approach as outlined may appear to heavy handed with the
use of `autoconf`. There are two other approaches that are possible:

1. Creating `configure` script using `sh` that determines the package sources
   and dynamically writes them to `src/Makevars` using `sed`.
    - [Jeroen Ooms](https://github.com/jeroen) out of 
      [rOpenSci](http://ropensci.org/) opts to call this approach `anticonf`. 
      An example of this approach can be seen in the [`curl` package](https://github.com/jeroen/curl/blob/master/configure#L1).
2. Attempting a wildcard approach specified in 
   [Section 1.2.1.3: Compiling in sub-directories](https://cran.r-project.org/doc/manuals/r-release/R-exts.html#Compiling-in-sub_002ddirectories) of 
   [Writing R Extensions](https://cran.r-project.org/doc/manuals/r-release/R-exts.html)

The first option is viable, but uncommon. I opted to avoid this implementation
to gently provide a standalone example of an `autoconf` setup.

Meanwhile, the second option ushers in trouble on later versions of R. In the
early commits, this was the main way I structured the package. Nowadays, this
approach will yield a **Warning** when checking the R package and attempts to
satisfy the check will cause a subsequent warning. 

In particular, the warning is given as: 

```bash
* checking for GNU extensions in Makefiles ... WARNING
Found the following file(s) containing GNU extensions:
  src/Makevars
Portable Makefiles do not use GNU extensions such as +=, :=, $(shell),
$(wildcard), ifeq ... endif. See section ‘Writing portable packages’ in
the ‘Writing R Extensions’ manual.
```

This can be resolved by modifying the `DESCRIPTION` file to include:

```bash
SystemRequirements: GNU make
```

Doing so will result in a `NOTE` being generated on subsequent checks though:

```bash
* checking for GNU extensions in Makefiles ... NOTE
GNU make is a SystemRequirements.
```

## License

GPL (\>= 2)