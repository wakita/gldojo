#include "Program.hpp"
#include "Utility.hpp"
#include "Point.hpp"

using namespace smartnova::gl;

class KW3 : public Application {
  virtual void init() {
    info.winWidth = 600;
    Application::init("kw3: 一頂点から三角形がたくさん");
  }

  Program program;
  Point *point;
  
  virtual void startup() {
    point = new Point(5);
    program.load("kw/kw3", "vs, tcs, tes, fs");
    program.use();
    glPointSize(5);
  }

  GLfloat bgcolor[4] = { 0, 0, 0, 0 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);
    point->render(t);
  }
};

DECLARE_MAIN(KW3)
