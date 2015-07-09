#include "vbotorus.h"

#include "Program.hpp"
#include "Utility.hpp"

using glm::radians;
using glm::rotate;
using glm::translate;

using namespace smartnova;
using namespace smartnova::gl;

class CB02A2 : public Application {
  public:
    CB02A2(json11::Json config) : Application(config) {}

    VBOTorus *Torus;
    vector<mat4> Views { mat4(1.f), mat4(1.f) };
    json11::Json motion;
    glm::vec2 initRot;
    glm::vec3 relocation;
    GLfloat rotY;

    virtual void init() {
      Application::init("");

      { vec4 _ = util::vec4(A["Torus"]);
        Torus = new VBOTorus(_[0], _[1], _[2], _[3]); }

      { json11::Json Look = A["Look"];
#     define LOOK(n) util::vec3(Look[n])
        Views[0] = glm::lookAt(LOOK("left"),  LOOK("at"), LOOK("up"));
        Views[1] = glm::lookAt(LOOK("right"), LOOK("at"), LOOK("up"));
      }

      motion = A["TorusMotion"];
      initRot = util::vec2(motion["InitRot"]);
      relocation = util::vec3(motion["Relocation"]);
      rotY = motion["RotY"].number_value();;
    }

    Program program;

    virtual void startup() {
      program.load(A["shaders"], 0);
      program.use();
      program.setUniforms("Material", A["Material"]);
      program.setUniforms("Light",    A["Light"]);

      glEnable(GL_DEPTH_TEST);
    }

    virtual void render(double t) {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      mat4 Model =
        translate(I4, relocation * t) *
        rotate(radians((float)t * rotY), Y) *
        rotate(radians(initRot.x), X) *
        rotate(radians(initRot.y), Y);

      for (int i = 0; i < Views.size(); i++) {
        mat4 View = Views.at(i);
        mat4 ModelView = View * Model;
        program.setUniform("ModelViewMatrix", ModelView);
        program.setUniform("NormalMatrix",    glm::inverseTranspose(mat3(ModelView)));
        program.setUniform("MVP",             Projection * ModelView);
        program.setUniform("FSMOD",           (GLint)i);
        program.setUniforms("Material",       A[i == 0 ? "MaterialL" : "MaterialR"]);
        Torus->render();
      }
    }
};

GLMAIN(CB02A2)
