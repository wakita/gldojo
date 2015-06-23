#include "Program.hpp"
#include "Utility.hpp"
#include "Point.hpp"

using namespace smartnova::gl;

class KW2 : public Application {
  virtual void init() {
    info.winWidth = 600;
    Application::init("kw1: 一頂点から三角形");
  }

  Program program;
  Point *point;
  
  virtual void startup() {
    point = new Point();
    program.load("kw/kw2", "vs, tcs, tes, fs");
    program.use();
    glPointSize(15);
  }

  GLfloat bgcolor[4] = { 0, 0, 0, 0 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);
    point->render(t);
  }
};

DECLARE_MAIN(KW2)
