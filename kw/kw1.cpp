#include "Program.hpp"
#include "Utility.hpp"
#include "RegularPolygon.hpp"

using namespace smartnova::gl;

class KW1 : public Application {
  virtual void init() {
    info.winWidth = 600;
    Application::init("kw1: 多角形");
  }

  Program program;
  RegularPolygon *RPolygon;
  
  virtual void startup() {
    RPolygon = new RegularPolygon(0.8f, 3);
    program.load("kw/kw1", "vs, fs");
    program.use();
  }

  GLfloat bgcolor[4] = { 0, 0, 0, 0 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);
    RPolygon->render(t);
  }
};

DECLARE_MAIN(KW1)
