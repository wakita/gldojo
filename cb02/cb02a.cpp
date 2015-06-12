#include "vbotorus.h"
#include "Program.hpp"

using glm::radians;
using glm::rotate;
using glm::lookAt;
using glm::perspective;

using namespace smartnova::gl;

class CB02A : public Application {
  virtual void init() {
    Application::init("cb02a: Phong's ADS (Ambient, Diffuse, and Specular) shading");
  }

  Program program;
  VBOTorus *torus;
  mat4 View = mat4(1.f);

  virtual void startup() {
    program.load("cb02/cb02a", vector<string> { "vs", "fs" });
    program.use();

    torus = new VBOTorus(0.7, 0.3, 50, 50);

    View = lookAt(vec3(0, 0, 2), vec3(0), Y);

    vec4 worldLight(5, 5, 2, 1);

    program.setUniform("Material.Kd", .9, .5, .3);
    program.setUniform("Material.Ka", .9, .5, .3);
    program.setUniform("Material.Ks", .8, .8, .8);
    program.setUniform("Material.Shininess", 100.0f);

    program.setUniform("Light.Position", View * worldLight );
    program.setUniform("Light.Ld", 1., 1., 1.);
    program.setUniform("Light.La", .4, .4, .4);
    program.setUniform("Light.Ls", 1., 1., 1.);

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

DECLARE_MAIN(CB02A)
