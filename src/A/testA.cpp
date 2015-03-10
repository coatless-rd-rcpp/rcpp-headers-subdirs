#include <RcppArmadillo.h>
#include "testA.h"
using namespace Rcpp;

// [[Rcpp::export]]
double testfunctionA(const arma::colvec & x) {
    double v = arma::as_scalar(x.t() * x);
    return v;
}
