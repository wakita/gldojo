#include "vboteapot.h"
#include "Program.hpp"
#include "Utility.hpp"

using glm::radians;
using glm::rotate;
using glm::translate;

using namespace smartnova;
using namespace smartnova::gl;

#define _DEBUG

class CB02C : public Application {
  json11::Json C;

  public:
  CB02C(json11::Json config) { C = config; }

  virtual void init() { Application::init(""); }

  Program program;
  VBOTeapot *shape;
  mat4 Model, View, ModelView;

  virtual void startup() {
    setTrace(C["trace"].bool_value());

    json11::Json app = C["app"], Look = app["Look"];
    {
#     define LOOK(n) util::vec3(Look[n])
      View = lookAt(LOOK("eye"), LOOK("at"), LOOK("up"));
    }

    Model = translate(util::vec3(app["TeapotMotion"]["Translate"])) * rotate(radians(-90.f), X);
    ModelView = View * Model;

    program.load(app["shaders"].array_items()[0]);
    program.use();

    shape = new VBOTeapot(app["Teapot"]["grid"].int_value(), mat4(1.f));

    program.setUniforms("Light",          app["Light"]);
    program.setUniforms("Material",       app["Material"]);

    program.setUniform("ModelViewMatrix", ModelView);
    program.setUniform("NormalMatrix",    glm::inverseTranspose(mat3(ModelView)));

    glEnable(GL_DEPTH_TEST);
    setTrace(false);
  }

  virtual void render(double t) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program.setUniform("MVP", Projection * ModelView);
    shape->render();
  }
};

GLMAIN(CB02C)
