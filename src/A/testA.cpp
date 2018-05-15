#include <RcppArmadillo.h>
#include "testA.h"
using namespace Rcpp;

// This function cannot be exported via Rcpp Attributes as
// it is in a subfolder for src/

double testfunctionA(const arma::colvec & x) {
    double v = arma::as_scalar(x.t() * x);
    return v;
}
