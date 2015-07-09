#include "vbotorus.h"
#include "Program.hpp"
#include "Utility.hpp"

using glm::radians;
using glm::rotate;
using glm::lookAt;
using glm::perspective;

using namespace smartnova;
using namespace smartnova::gl;

class CB02A : public Application {
  VBOTorus *Torus;
  mat4 View = mat4(1.f);
  vec2 initRot;
  GLfloat rotY;

  public:
  CB02A(json11::Json config) : Application(config) {}

  virtual void init() {
    Application::init();

    { vec4 _ = util::vec4(A["Torus"]);
      Torus = new VBOTorus(_[0], _[1], _[2], _[3]); }

    { json11::Json Look = A["Look"];
      View = lookAt(util::vec3(Look["eye"]), util::vec3(Look["at"]), util::vec3(Look["up"])); }

    initRot = util::vec2(A["TorusMotion"]["InitRot"]);
    rotY = A["TorusMotion"]["RotY"].number_value();
  }

  Program program;

  virtual void startup() {
    program.load(A["shaders"], 0);
    program.use();
    program.setUniforms("Material", A["Material"]);
    program.setUniforms("Light",    A["Light"]);

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
