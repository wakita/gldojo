#define _DEBUG
#include "Program.hpp"

using namespace smartnova::gl;

class AppTest : public Application {
  virtual void init() {
    Application::init(string("OpenGL App Framework Test"));
  }

  virtual void startup() {}

  const GLfloat bgcolor[4] = { 1.f, 0.f, 0.f, 1.f };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);
  }
};

DECLARE_MAIN(AppTest)
