#include <Rcpp.h>
#include "elo.h"
#include "glicko.h"
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

// [[Rcpp::export]]
std::map<std::string, std::vector<double>> ServeReturnGlicko(
    std::vector<std::string> server,
    std::vector<std::string> returner,
    std::vector<bool> server_won,
    std::vector<int> match_number,
    double match_to_match_variance,
    double initial_variance,
    double initial_return_rating=1410.,
    bool backward_pass=false) {

  return Glicko::CalculateServeReturnGlicko(server, returner, server_won,
      match_number, match_to_match_variance, initial_variance,
      initial_return_rating, backward_pass);

}

// [[Rcpp::export]]
std::vector<double> CalculateGlickoWinExpectation(
    std::vector<double> mu, std::vector<double> sigma_sq,
    std::vector<double> mu_j, std::vector<double> sigma_sq_j) {

  std::vector<double> expectations;

  for (int i = 0; i < sigma_sq_j.size(); i++) {

    expectations.emplace_back(Glicko::CalculateWinExp(mu[i], sigma_sq[i], mu_j[i],
          sigma_sq_j[i]));

  }

  return expectations;

}
