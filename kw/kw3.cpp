#include "Program.hpp"
#include "Utility.hpp"
#include "Point.hpp"

using namespace smartnova::gl;

class KW3 : public Application {
  virtual void init() {
    Application::init("kw3: 一頂点から三角形がたくさん");
  }

  Program program;
  unique_ptr<Point> point;
  
  virtual void startup() {
    program.load("kw/kw3", "vs, tcs, tes, fs");
    program.use();
    point.reset(new Point(5));
    glPointSize(5);
  }

  GLfloat bgcolor[4] = { 0, 0, 0, 0 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);
    point.get()->render(t);
  }
};

DECLARE_MAIN(KW3)
