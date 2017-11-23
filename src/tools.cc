#include "tools.h"

double Tools::LookPlayerUp(const std::string &player_name,
    const std::map<std::string, double> &ratings,
    double default_value) {

  auto it = ratings.find(player_name);

  if (it != ratings.end()) {
    return it->second;
  }
  else {
    return default_value;
  }
}
