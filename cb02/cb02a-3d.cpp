#include "vbotorus.h"
#include "Program.hpp"

using glm::radians;
using glm::rotate;
using glm::lookAt;
using glm::perspective;

using namespace smartnova::gl;

class CB02A : public Application {
  virtual void init() {
    info.winWidth = 1920; info.winHeight = 1080;
    // info.flags.fullscreen = 1;
    Application::init("cb02a: Phong's ADS (Ambient, Diffuse, and Specular) shading");
    cout << "width: " << info.winWidth << ", height: " << info.winHeight << endl;
  }

  Program program;
  VBOTorus *torus;
  mat4 View1 = mat4(1.f), View2 = mat4(1.f);

  virtual void startup() {
    program.load("cb02/cb02a", vector<string> { "vs", "fs" });
    program.use();

    torus = new VBOTorus(0.7, 0.3, 50, 50);

    View1 = lookAt(vec3(-.01, 0, 2), vec3(0), Y);
    View2 = lookAt(vec3( .01, 0, 2), vec3(0), Y);

    program.setUniform("Material.Kd", .9, .5, .3);
    program.setUniform("Material.Ka", .9, .5, .3);
    program.setUniform("Material.Ks", .8, .8, .8);
    program.setUniform("Material.Shininess", 100.0f);

    program.setUniform("Light.Ld", 1., 1., 1.);
    program.setUniform("Light.La", .4, .4, .4);
    program.setUniform("Light.Ls", 1., 1., 1.);

    glEnable(GL_DEPTH_TEST);
  }

  void onResize(GLFWwindow *win, int w, int h) {
    info.winWidth = w; info.winHeight = h;
    glViewport(0, 0, w, h);
    Projection = glm::perspective(glm::radians(70.0f), (float)w/h/2, 0.3f, 100.0f);
  }

  void render(double t) {
    int w2 = info.winWidth / 2, h = info.winHeight;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mat4 Model =
      rotate(radians((float)t * 8), Y) * rotate(radians(-35.f), X) * rotate(radians(35.f), Y);

    vec4 worldLight(5, 5, 2, 1);

    // Set matrices
    glViewport(0, 0, w2, h);
    mat4 ModelView = View2 * Model;
    program.setUniform("Light.Position", View2 * worldLight );
    program.setUniform("ModelViewMatrix", ModelView);
    program.setUniform("NormalMatrix", glm::inverseTranspose(mat3(ModelView)));
    program.setUniform("MVP", Projection * ModelView);

    torus->render();

    glViewport(w2, 0, w2, h);
    ModelView = View1 * Model;
    program.setUniform("Light.Position", View1 * worldLight );
    program.setUniform("ModelViewMatrix", ModelView);
    program.setUniform("NormalMatrix", glm::inverseTranspose(mat3(ModelView)));
    program.setUniform("MVP", Projection * ModelView);

    torus->render();

  }
};

DECLARE_MAIN(CB02A)
