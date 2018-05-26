# SubdirSrc

This project shows how to embed code in subdirectories within the `src/` folder by modifying the `Makevars` file, as specified in [Section: 1.2.1 Using Makevars](https://cran.r-project.org/doc/manuals/r-release/R-exts.html#Using-Makevars) of [Writing R Extensions](https://cran.r-project.org/doc/manuals/r-release/R-exts.html), which is a variant of [`Make`](https://www.gnu.org/software/make/manual/make.html) that is _unique_ to _R_.

**Note: There is no way to use [Rcpp Attributes in subfolders](http://lists.r-forge.r-project.org/pipermail/rcpp-devel/2015-March/008473.html).** That is, you cannot export a function in a subfolder using`// [[Rcpp::export]]`. Thus, you would need to create and export an intermediary function in `src/`, e.g. [`testfunction()`](https://github.com/coatless/header_cpp_subdir_code/blob/master/src/main.cpp#L7-L10) in [`main.cpp`](https://github.com/coatless/header_cpp_subdir_code/blob/master/src/main.cpp). Make sure to include the headers associated with the subdirectories and that the headers have an _inclusion guard_. 

In essence, this project shows how to go from:

```bash
src/
    |-> Makevars
    |-> Makevars.win
    |-> main.cpp
    |-> testA.cpp
    |-> testA.h
    |-> testB.cpp
    |-> testB.h
```

to: 


```bash
src/
    |-> Makevars
    |-> Makevars.win
    |-> main.cpp
    |-> A
        |-> testA.cpp
        |-> testA.h
    |-> B
        |-> testB.cpp
        |-> testB.h
```
