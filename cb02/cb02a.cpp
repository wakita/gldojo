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

    torus = new VBOTorus(0.7f, 0.3f, 50, 50);

    View = lookAt(vec3(0.f, 0.f, 2.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));

    vec4 worldLight = vec4(5.f, 5.f, 2.f, 1.f);

    program.setUniform("Material.Kd", .9, .5, .3);
    program.setUniform("Material.Ka", .9, .5, .3);
    program.setUniform("Material.Ks", .8, .8, .8);
    program.setUniform("Material.Shininess", 100.0f);

    program.setUniform("Light.Position", View * worldLight );
    program.setUniform("Light.Ld", 1., 1., 1.);
    program.setUniform("Light.La", .4, .4, .4);
    program.setUniform("Light.Ls", 1., 1., 1.);

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
      rotate(radians(-35.0f),   vec3(1.f,0.f,0.f)) *
      rotate(radians( 35.0f),   vec3(0.f,1.f,0.f));

    // Set matrices
    mat4 MV = View * Model;
    mat3 Normal = mat3(vec3(MV[0]), vec3(MV[1]), vec3(MV[2]));

    program.setUniform("ModelViewMatrix", MV);
    program.setUniform("NormalMatrix", Normal);
    program.setUniform("MVP", Projection * MV);

    torus->render();
  }
};

DECLARE_MAIN(CB02A)
