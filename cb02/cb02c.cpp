#include "vboteapot.h"
#include "Program.hpp"
#include "Utility.hpp"

using glm::radians;
using glm::rotate;
using namespace smartnova;
using namespace smartnova::gl;

class CB02C : public Application {
  json11::Json C = util::readConfig("cb02/cb02c");

  virtual void init() {
    Application::init("cb02c: Discard");
  }

# define FV(x) ((GLfloat)C[x].number_value())

  Program program;
  VBOTeapot *shape;
  json11::Json Look = C["Look"];
  const mat4
    Model =
    glm::translate(vec3(0.0, -1.5, 0.0)) * rotate(radians(-90.f), vec3(1, 0, 0)),
    View = lookAt(util::vec3(Look["eye"]), util::vec3(Look["at"]), util::vec3(Look["up"])),
    ModelView = View * Model;

  virtual void startup() {
    program.load("cb02/cb02c", "vs, fs");
    program.use();

    shape = new VBOTeapot(13, mat4(1.f));

    program.setUniforms("Light", C["Light"]);
    program.setUniforms("Material", C["Material"]);

    program.setUniform("ModelViewMatrix", ModelView);
    program.setUniform("NormalMatrix",    glm::inverseTranspose(mat3(ModelView)));

    glEnable(GL_DEPTH_TEST);
  }

  virtual void render(double t) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.setUniform("MVP", Projection * ModelView);

    shape->render();
  }
};

DECLARE_MAIN(CB02C)
