#include "Program.hpp"
#include "Utility.hpp"
#include "Point.hpp"

using namespace smartnova::gl;

class KW2 : public Application {
  public:
    KW2(Json config): Application(config) {}
    virtual void init() {
      Application::init();
    }

    Program program;
    unique_ptr<Point> point;

    virtual void startup() {
      program.load(A["shaders"], 0);
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

GLMAIN(KW2)
