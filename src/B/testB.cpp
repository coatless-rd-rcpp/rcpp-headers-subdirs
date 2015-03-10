#include <RcppArmadillo.h>
#include "testB.h"
using namespace Rcpp;

// [[Rcpp::export]]
double testfunctionB(const arma::colvec & x) {
    double v = arma::as_scalar(x.t() * x);
    return v;
}