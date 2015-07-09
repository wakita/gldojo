#include "vbotorus.h"
#include "Program.hpp"
#include "Utility.hpp"

using namespace smartnova;
using namespace smartnova::gl;

using glm::radians;
using glm::rotate;
using glm::lookAt;
using glm::perspective;

class CB02B : public Application {
  public:
    CB02B(json11::Json config): Application(config) { }

    VBOTorus *torus;
    mat4 View = mat4(1.f);

    virtual void init() {
      Application::init();
      { vec4 _ = util::vec4(A["Torus"]);
        torus = new VBOTorus(_[0], _[1], _[2], _[3]); }

      { json11::Json Look = A["Look"];
        View = lookAt(util::vec3(Look["eye"]), util::vec3(Look["at"]), util::vec3(Look["up"])); }
    }

    Program program;

    virtual void startup() {
      program.load(A["shaders"], 0);
      program.use();

      program.setUniform("Kd",            util::vec3(A["Material"]["Kd"]));
      program.setUniform("Ld",            util::vec3(A["Light"]["Ld"]));
      program.setUniform("LightPosition", util::vec4(A["WorldLight"]));

      glEnable(GL_DEPTH_TEST);
    }

    virtual void render(double t) {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      mat4 Model =
        rotate(radians((float)t * 8), Y) * rotate(radians(-35.f), X) * rotate(radians(35.f), Y);

      mat4 ModelView = View * Model;
      program.setUniform("ModelViewMatrix", ModelView);
      program.setUniform("NormalMatrix",    glm::inverseTranspose(mat3(ModelView)));
      program.setUniform("MVP",             Projection * ModelView);

      torus->render();
    }
};

GLMAIN(CB02B)
