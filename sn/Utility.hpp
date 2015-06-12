#pragma once

#include <stdexcept>
#include <json11.hpp>

namespace smartnova { namespace util {

class ProgramException : public std::runtime_error {
  public:
    ProgramException(const std::string & msg) : std::runtime_error(msg) {}
    ProgramException(const std::string & path, const std::string & msg) :
      runtime_error("\"" + path + "\": " + msg) {}
};

std::string readFile(const std::string &path)
  throw (ProgramException);

json11::Json readJSON(const std::string &path)
  throw (ProgramException);

json11::Json readConfig(const std::string &name)
  throw (ProgramException);

} }
