#include <Rcpp.h>
#include "routineA.h"

// This function cannot be exported via Rcpp Attributes as
// it is in a subdirectory of src/ and not immediately within src/
// Therefore, there is no [[Rcpp::export]] tag above the function.
//
// To access this function in R, you would have to create a function in src/
// that calls this function and is exported into R.

Rcpp::NumericVector calc_A_routine(Rcpp::NumericVector x) {
  Rcpp::NumericVector a = x - 4;
  return a;
}
