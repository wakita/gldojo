#pragma once

#include <stdexcept>

#define GLM_FORCE_CXX11
#define GLM_EXT_INCLUDED
#define GLM_FORCE_RADIANS
#define GLM_FORCE_SIZE_FUNC // vec4.length() => vec4.size()
#include <glm/glm.hpp>

#include <glbinding/gl43/gl.h>

#include <json11.hpp>

using json11::Json;

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

json11::Json readConfig()
  throw (ProgramException);

glm::vec3 rgb2hsv(const glm::vec3 &c);
glm::vec3 hsv2rgb(const glm::vec3 &c);

glm::vec2 vec2(const json11::Json &x);
glm::vec3 vec3(const json11::Json &x);
glm::vec4 vec4(const json11::Json &x);

} }
