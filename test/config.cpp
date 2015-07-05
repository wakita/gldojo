#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>

#include <json11.hpp>

#include "Program.hpp"

int main(int argc, char const * const argv[]) {
  std::string config_json("/Temp/config.json");

  std::ostringstream cmd;
  cmd << "node node_modules/config.js";
  for (auto && arg: std::vector<std::string> { argv + 1, argv + argc }) {
    cmd << " " << arg;
  }
  cmd << " > " << config_json.c_str();
  std::system(cmd.str().c_str());

  std::string err;
  Json config(Json::parse(smartnova::util::readFile(config_json), err));
  std::cout << config.dump() << std::endl;
}
