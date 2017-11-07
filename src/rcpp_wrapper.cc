#include <Rcpp.h>
#include "elo.h"
using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
std::map<std::string, std::vector<double>> ServeReturnEloStaticK(
            std::vector<std::string> server_names,
            std::vector<std::string> returner_names,
            std::vector<bool> server_won,
            double k,
            double return_starting_elo = 1410.) {

  return Elo::CalculateServeReturnEloStaticK(
      server_names, returner_names, server_won, k, return_starting_elo);

}
