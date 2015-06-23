#include "Program.hpp"
#include "Utility.hpp"
#include "RegularPolygon.hpp"

using namespace smartnova::gl;

class KW1 : public Application {
  virtual void init() {
    info.winWidth = 600;
    Application::init("kw1: 多角形");
  }

  RegularPolygon *polygon;
  
  virtual void startup() {
    Program program;
    program.load("kw/kw1", "vs, fs");
    program.use();

    polygon = new RegularPolygon(0.5f, 3);
  }

  GLfloat bgcolor[4] = { 0, 0, 0, 1 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);
    polygon->render(t);
  }
};

DECLARE_MAIN(KW1)
