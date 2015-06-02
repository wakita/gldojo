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

    torus = new VBOTorus(.7f, .3f, 50, 50);

    View = lookAt(vec3(0.f, 0.f, 2.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));

    program.setUniform("Kd", .9f, .5f, .3f);
    program.setUniform("Ld", 1.f, 1.f, 1.f);
    program.setUniform("LightPosition", View * vec4(5.f, 5.f, 2.f, 1.f));

    glEnable(GL_DEPTH_TEST);

    onResize(window, info.winWidth, info.winHeight);
  }

  mat4 Projection = mat4(1.f);

  virtual void onResize(GLFWwindow *win, int w, int h) {
    info.winWidth = w; info.winHeight = h;
    glViewport(0, 0, w, h);
    Projection = perspective(radians(70.0f), (float)w/h, 0.3f, 100.0f);
  }

  virtual void render(double t) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mat4 Model =
      rotate(radians((float)t * 8), vec3(0.f,1.f,0.f)) *
      rotate(radians(-35.0f),       vec3(1.f,0.f,0.f)) *
      rotate(radians( 35.0f),       vec3(0.f,1.f,0.f));

    // Set matrices
    mat4 MV = View * Model;
    program.setUniform("ModelViewMatrix", MV);
    program.setUniform("NormalMatrix",
        mat3(vec3(MV[0]), vec3(MV[1]), vec3(MV[2])));
    program.setUniform("MVP", Projection * MV);

    torus->render();

    showFPS(t);
  }
};

DECLARE_MAIN(CB02B)
