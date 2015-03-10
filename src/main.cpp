#include <RcppArmadillo.h>
#include "A/testA.h"
#include "B/testB.h"

using namespace Rcpp;

// [[Rcpp::export]]
double testfunction(const arma::colvec & x) {
    return testfunctionA(x) + testfunctionB(x);
}