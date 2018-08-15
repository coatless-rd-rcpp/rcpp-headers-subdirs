#include <Rcpp.h>

// Load subdirectory header files
#include "A/routineA.h"
#include "B/routineB.h"

//' Using Both Subdirectory Functions
//' 
//' These function serve as intermediaries between R and the subdirectory
//' source. 
//' 
//' @param x Vector of Numeric Values with length \eqn{n}.
//' 
//' @return A vector of numeric values with length \eqn{n}.
//' 
//' @rdname exported_funcs
//' @export
//' @examples
//' my_vec = c(3.5, 8, -1.5, -2, 0, 42)
//' calc_modifications(my_vec)
// [[Rcpp::export]]
Rcpp::NumericVector calc_modifications(Rcpp::NumericVector x) {
  
  // Calculate the modification from the A routine
  Rcpp::NumericVector A = calc_A_routine(x); 
  
  // Calculate the modification from the B routine
  Rcpp::NumericVector B = calc_B_routine(x); 
  
  // Calculate the element-wise total.
  Rcpp::NumericVector C = A + B;
  
  return C;
}

//' @rdname exported_funcs
//' @export
//' @details
//' The exported function name is different from the subdirectory function. 
//' C++ does not allow duplicate function names with the same parameters. To 
//' preserve the original function name necessitates the subdirectory function
//' being placed behind a namespace, e.g. `A::calc_A_routine()`. Otherwise,
//' the name of the function exported must be different, e.g. `calc_A_export()`.
//' 
//' @examples
//' my_vecA = c(881, 884, 1,2,-4)
//' calc_A_export(my_vec)
// [[Rcpp::export]]
Rcpp::NumericVector calc_A_export(Rcpp::NumericVector x) {
  
  // Calculate the modification from the A routine and return it
  return calc_A_routine(x); 
}


//' @rdname exported_funcs
//' @export
//' @examples
//' my_vecB = c(512,32, -1, 1.3, 5.9)
//' calc_B_export(my_vecB)
// [[Rcpp::export]]
Rcpp::NumericVector calc_B_export(Rcpp::NumericVector x) {
  
  // Calculate the modification from the B routine and return it
  return calc_B_routine(x); 
}