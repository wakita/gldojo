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

json11::Json readConfig(const std::string &name)
  throw (ProgramException) {
    const char *dir = getenv("CONFIG_DIR");
    const std::string base(dir ? dir : "config");
    return readJSON(base + "/" + name + ".json");
  }

#define FV(v, i) ((gl43::GLfloat)(v)[i].number_value())

glm::vec3 vec3(const json11::Json &x) {
  json11::Json::array v = x.array_items();
  return glm::vec3(FV(v, 0), FV(v, 1), FV(v, 2));
}

glm::vec4 vec4(const json11::Json &x) {
  json11::Json::array v = x.array_items();
  return glm::vec4(FV(v, 0), FV(v, 1), FV(v, 2), FV(v, 3));
}

} }
