#include "vbotorus.h"
#include "Program.hpp"

using namespace smartnova::gl;

using glm::radians;
using glm::rotate;
using glm::lookAt;
using glm::perspective;

class CB02B : public Application {
  virtual void init() {
    Application::init("cb02b: Diffuse shader");
  }

  Program program;
  VBOTorus *torus;
  mat4 View = mat4(1.f);

  virtual void startup() {
    program.load("cb02/cb02b", vector<string> { "vs", "fs" });
    program.use();

    torus = new VBOTorus(.7, .3, 50, 50);

    View = lookAt(vec3(0, 0, 2), vec3(0), Y);

    program.setUniform("Kd", .9, .5, .3);
    program.setUniform("Ld", 1., 1., 1.);
    program.setUniform("LightPosition", View * vec4(5, 5, 2, 1));

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
