#include <Rcpp.h>
#include "elo.h"
#include "glicko.h"
using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
std::map<std::string, std::vector<double>> CalculateEloWithStartingValues(
    std::vector<std::string> winner_names,
    std::vector<std::string> loser_names,
    std::vector<int> winner_match,
    std::vector<int> loser_match,
    std::vector<double> slam_factor,
    std::vector<std::string> known_elo_names,
    std::vector<double> known_elo_values) {

    std::map<std::string, double> last_elo_values;

    for (int i = 0; i < known_elo_names.size(); i++) {
      last_elo_values[known_elo_names[i]] = known_elo_values[i];
    }

    return Elo::CalculateElo(winner_names, loser_names, winner_match,
        loser_match, slam_factor, last_elo_values);

}

// [[Rcpp::export]]
std::map<std::string, std::vector<double>> CalculateElo(
    std::vector<std::string> winner_names,
    std::vector<std::string> loser_names,
    std::vector<int> winner_match,
    std::vector<int> loser_match,
    std::vector<double> slam_factor) {
    return Elo::CalculateElo(winner_names, loser_names, winner_match,
        loser_match, slam_factor);
}

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
