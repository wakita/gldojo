#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "Utility.hpp"

using namespace gl;

namespace smartnova { namespace util {

std::string readFile(const std::string &path)
  throw (smartnova::util::ProgramException) {
    std::ifstream f(path.c_str());
    if (!f) throw smartnova::util::ProgramException(path, "Unable to open a file (" + path + ")");
    return std::string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
  }

Json readJSON(const std::string &path)
  throw (smartnova::util::ProgramException) {
    std::string err;
    Json x(Json::parse(readFile(path), err));
    return x;
  }

Json readConfig(const std::string &name)
  throw (ProgramException) {
    const char *dir = getenv("CONFIG_DIR");
    const std::string base(dir ? dir : "config");
    return readJSON(base + "/" + name + ".json");
  }

Json readConfig()
  throw (ProgramException) {
    return readJSON(std::string(getenv("HOME")) + "/.gl-config.json");
  }

Json readConfig(char const * const argv[])
  throw (ProgramException) {
    const std::string command(argv[0]);
    std::string cmd = command.substr(command.find_last_of("\\") + 1);
    cmd = cmd.substr(0, cmd.find_last_of("."));
    if (cmd == "run-nvidia" || cmd == "run-intel") cmd = argv[1];
    std::string json_path(std::string(getenv("HOME")) + "/.gldojo/" + cmd + ".json");
    std::cout << json_path << std::endl;
    return readJSON(json_path);
  }

glm::vec3 rgb2hsv(const glm::vec3 &c) {
  int r = (int)(255 * c.r), g = (int)(255 * c.g), b = (int)(255 * c.b);
  int max = r > g ? (r > b ? r : b) : (g > b ? g : b);
  int min = r < g ? (r < b ? r : b) : (g < b ? g : b);
  int d = max - min;
  int hue =
    d == 0 ? 0 :
    max == r ? (60 * (g - b) / d + 360) % 360 :
    max == g ? (60 * (b - r) / d + 120) :
    (60 * (r - g) / d + 240);
  GLfloat saturation = (max == 0) ? (GLfloat)0.f : ((GLfloat) d / max);
  return glm::vec3(hue / 360.f, saturation, max / 256.f);
}

#define FV(v, i) ((gl::GLfloat)(v)[i].number_value())

glm::vec2 vec2(const Json &x) {
  Json::array v = x.array_items();
  return glm::vec2(FV(v, 0), FV(v, 1));
}

glm::vec3 vec3(const Json &x) {
  Json::array v = x.array_items();
  return glm::vec3(FV(v, 0), FV(v, 1), FV(v, 2));
}

glm::vec4 vec4(const Json &x) {
  Json::array v = x.array_items();
  return glm::vec4(FV(v, 0), FV(v, 1), FV(v, 2), FV(v, 3));
}

} }
