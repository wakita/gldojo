#include <fstream>

namespace smartnova::util;

std::string readFile(const std::string &path)
  throw (ProgramException) {
  ifstream f(path.c_str());
  if (!f) throw ProgramException(path, "Unable to open a file (" + path ")");
  return std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
}
