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

  Program program;
  VBOTeapot *shape;
  const mat4
    Model =
    glm::translate(vec3(0.0, -1.5, 0.0)) * rotate(radians(-90.f), vec3(1, 0, 0)),
    View = lookAt(vec3(0, 0, 7), vec3(0), Y),
    ModelView = View * Model;

  virtual void startup() {
    program.load("cb02/cb02c", vector<string> { "vs", "fs" });
    program.use();

    shape = new VBOTeapot(13, mat4(1.f));

    program.setUniform("Light.Ld",       1., 1., 1.);
    program.setUniform("Light.La",       .4, .4, .4);
    program.setUniform("Light.Ls",       1., 1., 1.);
    program.setUniform("Light.Position", vec4(0, 0, 0, 1));

    program.setUniform("Material.Kd",        .9, .5, .3);
    program.setUniform("Material.Ka",        .9, .5, .3);
    program.setUniform("Material.Ks",        .8, .8, .8);
    program.setUniform("Material.Shininess", 100.);

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
