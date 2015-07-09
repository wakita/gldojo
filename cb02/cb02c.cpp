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
  public:
  CB02C(json11::Json config) : Application(config) {}

  Program program;
  VBOTeapot *shape;
  mat4 Model, View, ModelView;

  virtual void init() {
    Application::init("");

    shape = new VBOTeapot(A["Teapot"]["grid"].int_value(), mat4(1.f));

    { json11::Json Look = A["Look"];
      View = lookAt(util::vec3(Look["eye"]), util::vec3(Look["at"]), util::vec3(Look["up"])); }

    Model = translate(util::vec3(A["Teapot"]["Translate"])) * rotate(radians(-90.f), X);
    ModelView = View * Model;
  }

  virtual void startup() {
    setTrace(C["trace"].bool_value());

    program.load(A["shaders"], 0);
    program.use();
    program.setUniforms("Light",          A["Light"]);
    program.setUniforms("Material",       A["Material"]);
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
