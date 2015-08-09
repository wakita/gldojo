#include "Program.hpp"
#include "Utility.hpp"
#include "SGP1.hpp"
#include "SGP4.hpp"

using namespace smartnova;
using namespace smartnova::gl;

class SphereApp: public Application {
  public: SphereApp(Json config): Application(config) {}

  virtual void init() {
    Application::init();
  }

  Program program;
  unique_ptr<SG> volume;

  virtual void startup() {
    glEnable(GL_DEPTH_TEST);

    program.load(A["shaders"], 0);
    program.use();

    string TEST(A["TEST"].string_value());
#   define DISPATCH(X) if (TEST == #X) volume.reset(new SG##X(&A, &program, &Projection))
    DISPATCH(P1);
    //DISPATCH(P2);
    //DISPATCH(P3);
    DISPATCH(P4);
    //DISPATCH(P5);
    //DISPATCH(I1);
    //DISPATCH(I2);
    //DISPATCH(C1);
    //DISPATCH(C2);
  }

  GLfloat bgcolor[4] = { .1f, .1f, .1f, 1.f };
  virtual void render(double t) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearBufferfv(GL_COLOR, 0, bgcolor);
    volume.get() -> render(t);
  }

  virtual void render() { render(0); }
};

GLMAIN(SphereApp)
