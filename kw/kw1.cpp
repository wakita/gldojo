#include "Program.hpp"
#include "Utility.hpp"
#include "RegularPolygon.hpp"

using namespace smartnova::gl;

class KW1 : public Application {
  public:
    KW1(json11::Json config): Application(config) {}

  virtual void init() {
    Application::init();
  }

  unique_ptr<RegularPolygon> polygon;
  
  virtual void startup() {
    Program program;
    program.load(A["shaders"], 0);
    program.use();

    polygon.reset(new RegularPolygon(0.5f, 3));
  }

  GLfloat bgcolor[4] = { 0, 0, 0, 1 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);
    polygon.get()->render(t);
  }
};

GLMAIN(KW1)
