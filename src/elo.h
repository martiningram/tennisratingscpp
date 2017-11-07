#ifndef ELO_H
#define ELO_H

#include <vector>
#include <map>
#include <string>

namespace Elo{

  std::map<std::string, std::vector<double>> CalculateStaticKElo(
            std::vector<std::string> winner_names,
            std::vector<std::string> loser_names,
            double k);

  std::map<std::string, std::vector<double>> CalculateServeReturnEloStaticK(
            std::vector<std::string> server_names,
            std::vector<std::string> returner_names,
            std::vector<bool> server_won,
            double k,
            double return_starting_elo = 1410.);

  double WinProbabilityP1(double elo_p1, double elo_p2);

  double LookPlayerUp(const std::string &player_name,
      const std::map<std::string, double> &ratings,
      double default_value = 1500.);

  double MakeUpdate(double old_elo, int outcome, double k,
      double win_expectation);

}

#endif
