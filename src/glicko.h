#ifndef GLICKO_H
#define GLICKO_H

#include <math.h>
#include <string>
#include <vector>
#include <map>

namespace Glicko {

  const double q = log(10) / 400;

  double CalculateG(double sigma_sq);

  double CalculateWinExpFitting(double mu, double mu_j, double sigma_sq_j);

  double CalculateDeltaSq(double mu, const std::vector<double>& mu_j,
      const std::vector<double>& sigma_sq_j, const std::vector<int>& n_j);

  double CalculateSingleMuUpdate(double mu, double sigma_sq, double mu_j,
      double sigma_sq_j, int outcome, double delta_sq);

  double CalculateSigmaSqPrime(double sigma_sq, double delta_sq);

  double CalculateWinExp(double mu, double sigma_sq, double mu_j, double
      sigma_sq_j);

  std::map<std::string, std::vector<double>> CalculateServeReturnGlicko(
      std::vector<std::string> server,
      std::vector<std::string> returner,
      std::vector<bool> server_won,
      std::vector<int> match_number,
      double match_to_match_variance,
      double initial_variance,
      double initial_return_rating=1410.);

  void AddVariance(std::map<std::string, double>& sigma_map,
      double variance_to_add, std::vector<std::string>& players);

  std::pair<double, double> CalculateSingleMatchUpdates(
      double mu, double sigma_sq, double mu_j, double sigma_sq_j,
      int outcome);

}

#endif
