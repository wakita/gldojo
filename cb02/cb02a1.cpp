#include "vbotorus.h"
#include "Program.hpp"
#include "Utility.hpp"

using glm::radians;
using glm::rotate;

using namespace smartnova;
using namespace smartnova::gl;

class CB02A : public Application {
  json11::Json C, app;

  public:
  CB02A(json11::Json config) {
    C = config;
    app = C["app"];
  }

  virtual void init() { Application::init(""); }

  Program program;
  VBOTorus *Torus;
  vec2 initRot;
  mat4 View = mat4(1.f);
  GLfloat rotY;

  virtual void startup() {
    program.load(app["shaders"].array_items()[0]);
    program.use();

    { vec4 _ = util::vec4(app["Torus"]);
      Torus = new VBOTorus(_[0], _[1], _[2], _[3]); }

    { json11::Json Look = app["Look"];
      View = glm::lookAt(util::vec3(Look["eye"]), util::vec3(Look["at"]), util::vec3(Look["up"])); }

    vec4 worldLight = util::vec4(app["WorldLight"]);

    program.setUniforms("Material", app["Material"]);
    program.setUniforms("Light",    app["Light"]);

    initRot = util::vec2(app["TorusMotion"]["InitRot"]);
    rotY = app["TorusMotion"]["RotY"].number_value();

    glEnable(GL_DEPTH_TEST);
  }

  virtual void render(double t) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mat4 Model =
      rotate(radians((float)t * rotY), Y) *
      rotate(radians(initRot.x), X) *
      rotate(radians(initRot.y), Y);
    mat4 ModelView = View * Model;

    program.setUniform("ModelViewMatrix", ModelView);
    program.setUniform("NormalMatrix",    glm::inverseTranspose(mat3(ModelView)));
    program.setUniform("MVP",             Projection * ModelView);

    Torus->render();
  }
};

GLMAIN(CB02A)
