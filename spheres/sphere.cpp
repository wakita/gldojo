#include "Program.hpp"
#include "Utility.hpp"
#include "SGP4.hpp"

using namespace smartnova;
using namespace smartnova::gl;

class SphereApp: public Application {
  public: SphereApp(Json config): Application(config) {}

  mat4 Model = mat4(1), View;

  virtual void init() {
    Application::init();
    { Json Look = A["Look"];
      vec3 LookEye = util::vec3(Look["eye"]);
      vec3 LookAt  = util::vec3(Look["at"]);
      vec3 LookUp  = util::vec3(Look["up"]);
      View = lookAt(LookEye, LookAt, LookUp);
    }
  }

  Program program;
  unique_ptr<Volume> volume;

  virtual void startup() {
    glEnable(GL_DEPTH_TEST);

    program.load(A["shaders"], 0);
    program.use();
    program.setUniform("PointSize", A["PointSize"].number_value());
    program.setUniform("Light", glm::normalize(util::vec3(A["WorldLight"])));

    const int SIZE = A["SIZE"].int_value();
    const GLfloat R = A["PointSize"].number_value();

    string TEST(A["TEST"].string_value());
#   define DISPATCH(X) if (TEST == #X) volume.reset(new SG##X(R, SIZE))
    //DISPATCH(P1);
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

    program.setUniform("MVP", Projection * View * Model);
    volume.get() -> render();
  }
};

GLMAIN(SphereApp)
