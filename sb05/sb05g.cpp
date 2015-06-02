#define _DEBUG
#include "Program.hpp"

using namespace smartnova::gl;

class Chapter5G : public Application {
  virtual void init() {
    Application::init("chap05g: Shader storage block の利用");
  }

  Program program;

  virtual void startup() {
    glGetError();
    program.load("sb05/sb05g", vector<string>{ "vs" });
  }

  GLfloat bgcolor[4] = { .2, .2, .2, 1 };
  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    program.use();
  }
};

DECLARE_MAIN(Chapter5G)
