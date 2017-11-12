#ifndef TOOLS_H
#define TOOLS_H

#include <map>
#include <string>

namespace Tools {

  double LookPlayerUp(const std::string &player_name,
      const std::map<std::string, double> &ratings,
      double default_value = 1500.);

}

#endif
