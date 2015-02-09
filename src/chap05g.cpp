#include <cmath>

#define _DEBUG
#include "sngl.hpp"
#include "snshader.hpp"

using namespace sn::gl;

class Chapter5G : public Application {
  virtual void init() {
    Application::init();
    info.title = "chap05g: Shader storage block の利用";
  }

  GLuint program;

  virtual void startup() {
    glGetError();
    program = program::link(shader::load("chap05g",
          std::vector<std::string> { ".vs" }), true);
  }

  GLfloat bgcolor[4] = { .2, .2, .2, 1 };
  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    glUseProgram(program);
  }
};

DECLARE_MAIN(Chapter5G)
