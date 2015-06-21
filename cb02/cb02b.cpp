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
  json11::Json C = util::readConfig("cb02/cb02b");

  virtual void init() {
    Application::init("cb02b: Diffuse shader");
  }

  Program program;
  VBOTorus *torus;
  mat4 View = mat4(1.f);

  virtual void startup() {
    program.load("cb02/cb02b", vector<string> { "vs", "fs" });
    program.use();

    { vec4 _ = util::vec4(C["Torus"]);
      torus = new VBOTorus(_[0], _[1], _[2], _[3]); }

    { json11::Json Look = C["Look"];
      View = lookAt(util::vec3(Look["eye"]), util::vec3(Look["at"]), util::vec3(Look["up"])); }

#   define FV(x) ((GLfloat)C[x].number_value())

    program.setUniform("Kd", FV("Kd"));
    program.setUniform("Ld", FV("Ld"));
    program.setUniform("LightPosition", FV("LightPosition"));

    glEnable(GL_DEPTH_TEST);
  }

  virtual void render(double t) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mat4 Model =
      rotate(radians((float)t * 8), Y) * rotate(radians(-35.f), X) * rotate(radians(35.f), Y);

    // Set matrices
    mat4 ModelView = View * Model;
    program.setUniform("ModelViewMatrix", ModelView);
    program.setUniform("NormalMatrix", glm::inverseTranspose(mat3(ModelView)));
    program.setUniform("MVP", Projection * ModelView);

    torus->render();
  }
};

DECLARE_MAIN(CB02B)
