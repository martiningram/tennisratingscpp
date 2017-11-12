#include "elo.h"
#include "tools.h"
#include <cmath>

double Elo::WinProbabilityP1(double elo_p1, double elo_p2){

  return 1. / (1. + std::pow(10., ((elo_p2 - elo_p1)/400.)));

}

double Elo::MakeUpdate(double old_elo, int outcome, double k,
    double win_expectation) {

  double update = k * (outcome - win_expectation);
  return old_elo + update;

}

std::map<std::string, std::vector<double>> Elo::CalculateStaticKElo(
      std::vector<std::string> winner_names,
      std::vector<std::string> loser_names, double k) {

  std::map<std::string, std::vector<double>> elos_over_time;
  std::map<std::string, double> last_elo_values;

  for (int i = 0; i < winner_names.size(); i++) {

    double winner_elo = Tools::LookPlayerUp(winner_names[i], last_elo_values);
    double loser_elo = Tools::LookPlayerUp(loser_names[i], last_elo_values);

    elos_over_time[std::string("winner_elo")].emplace_back(winner_elo);
    elos_over_time[std::string("loser_elo")].emplace_back(loser_elo);

    double winner_prob = Elo::WinProbabilityP1(winner_elo, loser_elo);

    last_elo_values[winner_names[i]] = Elo::MakeUpdate(
        winner_elo, 1, k, winner_prob);

    last_elo_values[loser_names[i]] = Elo::MakeUpdate(
        loser_elo, 0, k, 1 - winner_prob);

  }

  return elos_over_time;

}

std::map<std::string, std::vector<double>> Elo::CalculateServeReturnEloStaticK(
            std::vector<std::string> server_names,
            std::vector<std::string> returner_names,
            std::vector<bool> server_won,
            double k,
            double return_starting_elo) {

  std::map<std::string, std::vector<double>> elos_over_time;
  std::map<std::string, double> last_serve_elos;
  std::map<std::string, double> last_return_elos;

  for (int i = 0; i < server_names.size(); i++) {

    std::string &cur_server = server_names[i];
    std::string &cur_returner = returner_names[i];

    double server_elo = Tools::LookPlayerUp(cur_server, last_serve_elos);
    double returner_elo = Tools::LookPlayerUp(cur_returner, last_return_elos,
        return_starting_elo);

    elos_over_time["server_elos"].emplace_back(server_elo);
    elos_over_time["returner_elos"].emplace_back(returner_elo);

    double server_win_prob = Elo::WinProbabilityP1(server_elo, returner_elo);

    last_serve_elos[cur_server] = Elo::MakeUpdate(
        server_elo, server_won[i], k, server_win_prob);

    last_return_elos[cur_returner] = Elo::MakeUpdate(
        returner_elo, 1 - server_won[i], k, 1 - server_win_prob);

  }

  return elos_over_time;

}
