#include "glicko.h"
#include "tools.h"
#include <math.h>
#include <map>
#include <vector>
#include <string>

double Glicko::CalculateG(double sigma_sq) {

  return 1. / (sqrt(1 + 3 * pow(Glicko::q, 2) * sigma_sq / pow(M_PI, 2)));

}

double Glicko::CalculateWinExpFitting(double mu, double mu_j,
    double sigma_sq_j) {

  double g = Glicko::CalculateG(sigma_sq_j);
  return 1. / (1 + pow(10., -g * (mu - mu_j) / 400.));

}

double Glicko::CalculateDeltaSq(double mu, const std::vector<double>& mu_j,
    const std::vector<double>& sigma_sq_j, const std::vector<int>& n_j) {

  double total = 0.;

  for (int i = 0; i < mu_j.size(); i++) {

    double cur_g_sq = pow(Glicko::CalculateG(sigma_sq_j[i]), 2);
    double cur_win_exp = Glicko::CalculateWinExpFitting(mu, mu_j[i],
        sigma_sq_j[i]);

    double cur_total = pow(Glicko::q, 2.) * n_j[i] * cur_g_sq * cur_win_exp * (1
        - cur_win_exp);

    total = total + cur_total;

  }

  return pow(total, -1.);

}

double Glicko::CalculateSingleMuUpdate(double mu, double sigma_sq, double mu_j,
    double sigma_sq_j, int outcome, double delta_sq) {

  double pre_factor = Glicko::q / ((1. / sigma_sq) + (1. / delta_sq));
  double win_exp = Glicko::CalculateWinExpFitting(mu, mu_j, sigma_sq_j);
  double main_factor = Glicko::CalculateG(sigma_sq_j) * (outcome - win_exp);

  return pre_factor * main_factor;

}

double Glicko::CalculateSigmaSqPrime(double sigma_sq, double delta_sq) {

  return pow((1. / sigma_sq) + (1. / delta_sq), -1.);

}

void Glicko::AddVariance(std::map<std::string, double>& player_variances,
    double variance_to_add, std::vector<std::string>& players) {
  for (std::string& cur_player : players) {
    player_variances[cur_player] += variance_to_add;
  }
}

std::pair<double, double> Glicko::CalculateSingleMatchUpdates(
    double mu, double sigma_sq, double mu_j, double sigma_sq_j, int outcome) {

    double delta_sq = Glicko::CalculateDeltaSq(
        mu, std::vector<double> {mu_j},
        std::vector<double> {sigma_sq_j},
        std::vector<int> {1});

    double mu_update = Glicko::CalculateSingleMuUpdate(
        mu, sigma_sq, mu_j, sigma_sq_j, outcome, delta_sq);

    double new_mu = mu + mu_update;
    double new_sigma_sq = Glicko::CalculateSigmaSqPrime(sigma_sq, delta_sq);

    return std::make_pair(new_mu, new_sigma_sq);

}

std::map<std::string, std::vector<double>> Glicko::CalculateServeReturnGlicko(
      std::vector<std::string> server,
      std::vector<std::string> returner,
      std::vector<bool> server_won,
      std::vector<int> match_number,
      double match_to_match_variance,
      double initial_variance,
      double initial_return_rating) {

  // This is getting a little messy. It might be nice to have a class or struct
  // which handles these.
  std::map<std::string, double> last_serve_mu;
  std::map<std::string, double> last_return_mu;
  std::map<std::string, double> last_serve_sigma_sq;
  std::map<std::string, double> last_return_sigma_sq;

  std::map<std::string, std::vector<double>> ratings_history;

  int last_match_number = match_number[0];

  std::string cur_server;
  std::string cur_returner;

  for (int i = 0; i < server.size(); i++) {

    int cur_match_number = match_number[i];

    if (cur_match_number != last_match_number) {

      std::vector<std::string> players {cur_server, cur_returner};

      // Add the variance
      Glicko::AddVariance(last_serve_sigma_sq, match_to_match_variance,
          players);
      Glicko::AddVariance(last_return_sigma_sq, match_to_match_variance,
          players);

    }

    last_match_number = cur_match_number;

    cur_server = server[i];
    cur_returner = returner[i];
    int cur_outcome = server_won[i];

    // Find the current relevant values
    double cur_mu = Tools::LookPlayerUp(cur_server, last_serve_mu,
        1500.);

    double cur_sigma_sq = Tools::LookPlayerUp(cur_server, last_serve_sigma_sq,
        initial_variance);

    double cur_mu_j = Tools::LookPlayerUp(cur_returner, last_return_mu,
        initial_return_rating);

    double cur_sigma_sq_j = Tools::LookPlayerUp(cur_returner,
        last_return_sigma_sq, initial_variance);

    ratings_history["serve_mu"].emplace_back(cur_mu);
    ratings_history["serve_sigma_sq"].emplace_back(cur_sigma_sq);
    ratings_history["return_mu"].emplace_back(cur_mu_j);
    ratings_history["return_sigma_sq"].emplace_back(cur_sigma_sq_j);

    double new_server_mu;
    double new_server_sigma_sq;

    std::tie(new_server_mu, new_server_sigma_sq) =
      Glicko::CalculateSingleMatchUpdates(cur_mu, cur_sigma_sq, cur_mu_j,
          cur_sigma_sq_j, cur_outcome);

    double new_returner_mu;
    double new_returner_sigma_sq;

    std::tie(new_returner_mu, new_returner_sigma_sq) =
      Glicko::CalculateSingleMatchUpdates(cur_mu_j, cur_sigma_sq_j, cur_mu,
          cur_sigma_sq, 1 - cur_outcome);

    // Update the last seen values
    last_serve_mu[cur_server] = new_server_mu;
    last_serve_sigma_sq[cur_server] = new_server_sigma_sq;
    last_return_mu[cur_returner] = new_returner_mu;
    last_return_sigma_sq[cur_returner] = new_returner_sigma_sq;

  }

  return ratings_history;

}

double Glicko::CalculateWinExp(double mu, double sigma_sq, double mu_j,
    double sigma_sq_j) {

  double cur_g = Glicko::CalculateG(sigma_sq + sigma_sq_j);
  return 1. / (1. + pow(10., -cur_g * (mu - mu_j) / 400.));

}
