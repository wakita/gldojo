#include "vbotorus.h"
#include "Program.hpp"
#include "Utility.hpp"

using glm::radians;
using glm::rotate;

using namespace smartnova;
using namespace smartnova::gl;

class CB02A : public Application {
  json11::Json C;

  virtual void init() {
    Application::init("cb02a: Phong's ADS (Ambient, Diffuse, and Specular) shading");
    C = util::readConfig("cb02/cb02a");
  }

  Program program;
  VBOTorus *Torus;
  mat4 View = mat4(1.f);

  virtual void startup() {
    program.load("cb02/cb02a", vector<string> { "vs", "fs" });
    program.use();

    { vec4 _ = util::vec4(C["Torus"]);
      Torus = new VBOTorus(_[0], _[1], _[2], _[3]); }

    { json11::Json Look = C["Look"];
      View = glm::lookAt(util::vec3(Look["eye"]), util::vec3(Look["at"]), util::vec3(Look["up"])); }

    vec4 worldLight = util::vec4(C["WorldLight"]);

    program.setUniforms("Material", C["Material"]);
    program.setUniforms("Light", C["Light"]);

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

    Torus->render();
  }
};

DECLARE_MAIN(CB02A)
