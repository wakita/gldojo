#include "vboteapot.h"
#include "Program.hpp"

using glm::radians;
using glm::rotate;
using namespace smartnova::gl;

class CB02C : public Application {
  virtual void init() {
    Application::init("cb02c: Discard");
  }

  Program program;
  VBOTeapot *shape;
  const mat4
    Model =
    glm::translate(vec3(0.0, -1.5, 0.0)) * rotate(radians(-90.f), vec3(1.f, 0.f, 0.f)),
    View = lookAt(vec3(0.f, 0.f, 7.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f)),
    MV = View * Model;

  virtual void startup() {
    program.load("cb02/cb02c", vector<string> { "vs", "fs" });
    program.use();

    shape = new VBOTeapot(13, mat4(1.f));

    program.setUniform("Light.Ld",       1.f, 1.f, 1.f);
    program.setUniform("Light.La",       .4f, .4f, .4f);
    program.setUniform("Light.Ls",       1.f, 1.f, 1.f);
    program.setUniform("Light.Position", vec4(0.f, 0.f, 0.f, 1.f));

    program.setUniform("Material.Kd",        .9f, .5f, .3f);
    program.setUniform("Material.Ka",        .9f, .5f, .3f);
    program.setUniform("Material.Ks",        .8f, .8f, .8f);
    program.setUniform("Material.Shininess", 100.f);

    program.setUniform("ModelViewMatrix", MV);
    program.setUniform("NormalMatrix",    mat3(vec3(MV[0]), vec3(MV[1]), vec3(MV[2])));

    glEnable(GL_DEPTH_TEST);

    onResize(window, info.winWidth, info.winHeight);
  }

  mat4 Projection = mat4(1.f);

  virtual void onResize(GLFWwindow *win, int w, int h) {
    info.winWidth = w; info.winHeight = h;
    glViewport(0, 0, w, h);
    Projection = glm::perspective(radians(50.0f), (float)w / h, .3f, 100.f);
  }

  virtual void render(double t) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.setUniform("MVP", Projection * MV);

    shape->render();
  }
};

DECLARE_MAIN(CB02C)
