#pragma once

namespace smartnova {
  namespace util {

class ProgramException : public std::runtime_error {
  public:
    ProgramException(const std::string & msg) : runtime_error(msg) {}
    ProgramException(const std::string & path, const std::string & msg) :
      runtime_error("\"" + path + "\": " + msg) {}
};

std::string readFile(const std::string &path)
  throw (ProgramException);

} }
