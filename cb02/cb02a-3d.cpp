#include "vbotorus.h"
#include "Program.hpp"
#include "Utility.hpp"

using glm::radians;
using glm::rotate;
using glm::lookAt;
using glm::perspective;

using namespace smartnova;
using namespace smartnova::gl;

class CB02A_3D : public Application {
  json11::Json C = util::readConfig("cb02/cb02a");

  virtual void init() {
    info.winWidth = 1920; info.winHeight = 1080;
    Application::init("cb02a: Phong's ADS (Ambient, Diffuse, and Specular) shading");
    cout << "width: " << info.winWidth << ", height: " << info.winHeight << endl;
  }

  Program program;
  VBOTorus *Torus;
  mat4 View1 = mat4(1.f), View2 = mat4(1.f);

  virtual void startup() {
    program.load("cb02/cb02a", vector<string> { "vs", "fs" });
    program.use();

    { vec4 _ = util::vec4(C["Torus"]);
      Torus = new VBOTorus(_[0], _[1], _[2], _[3]); }

    { json11::Json Look = C["Look"];
      View1 = glm::lookAt(util::vec3(Look["left"]),
          util::vec3(Look["at"]), util::vec3(Look["up"]));
      View2 = glm::lookAt(util::vec3(Look["right"]),
          util::vec3(Look["at"]), util::vec3(Look["up"])); }

    View1 = lookAt(vec3(-.01, 0, 2), vec3(0), Y);
    View2 = lookAt(vec3( .01, 0, 2), vec3(0), Y);

    program.setUniforms("Material", C["Material"]);
    program.setUniforms("Light", C["Light"]);

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

    vec4 worldLight = util::vec4(C["WorldLight"]);

    glViewport(0, 0, w2, h);
    mat4 ModelView = View1 * Model;
    program.setUniform("Light.Position", View1 * worldLight );
    program.setUniform("ModelViewMatrix", ModelView);
    program.setUniform("NormalMatrix", glm::inverseTranspose(mat3(ModelView)));
    program.setUniform("MVP", Projection * ModelView);
    Torus->render();

    glViewport(w2, 0, w2, h);
    ModelView = View2 * Model;
    program.setUniform("Light.Position", View2 * worldLight );
    program.setUniform("ModelViewMatrix", ModelView);
    program.setUniform("NormalMatrix", glm::inverseTranspose(mat3(ModelView)));
    program.setUniform("MVP", Projection * ModelView);
    Torus->render();
  }
};

DECLARE_MAIN(CB02A_3D)
