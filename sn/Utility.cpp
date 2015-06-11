#include <fstream>

#include "Utility.hpp"

namespace smartnova { namespace util {

std::string readFile(const std::string &path)
  throw (smartnova::util::ProgramException) {
    std::ifstream f(path.c_str());
    if (!f) throw smartnova::util::ProgramException(path, "Unable to open a file (" + path + ")");
    return std::string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
  }

json11::Json readJSON(const std::string &path)
  throw (smartnova::util::ProgramException) {
    std::string err;
    json11::Json x(json11::Json::parse(readFile(path), err));
    return x;
  }

} }
