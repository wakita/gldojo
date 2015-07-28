#include "Program.hpp"
#include "Utility.hpp"
#include "PointGrid.hpp"

using namespace smartnova;
using namespace smartnova::gl;

class MouseEvent {
  public:
    double clickedX = -1, clickedY = -1;
    bool shouldHandle() { return clickedX != -1; }
    void shouldHandle(GLFWwindow *win, int button, int action, int mods) {
      glfwGetCursorPos(win, &clickedX, &clickedY);
      std::cout << "Clicked position: " << clickedX << ", " << clickedY << std::endl;
    }
    void clear() { clickedX = clickedY = -1; }
};

MouseEvent mouseEvent;

struct SSB {
  GLint  pick_oid;
  GLfloat pick_z;
};

class KW8: public Application {
  public: KW8(Json config): Application(config) {}

  mat4 Model = mat4(1), View;

  virtual void init() {
    Application::init();

    { Json Look = A["Look"];
      vec3 LookEye = util::vec3(Look["eye"]);
      vec3 LookAt  = util::vec3(Look["at"]);
      vec3 LookUp  = util::vec3(Look["up"]);
      View = lookAt(LookEye, LookAt, LookUp);
    }
  }

  enum { POS };
  Program program;
  unique_ptr<PointGrid> points;

  virtual void startup() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_POINT_SPRITE);

    program.load(A["shaders"], 0);
    program.use();
    program.setUniform("PointSize", A["PointSize"].number_value());
    program.setUniform("Light", glm::normalize(util::vec3(A["WorldLight"])));

    points.reset(new PointGrid(1.f, A["DIM"].int_value()));

    { // Prepare a shader storage buffer
      struct SSB ssb = { -1, -1000.f };
      GLuint ssbo;
      glGenBuffers(1, &ssbo);
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
      glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(SSB), &ssb, GL_DYNAMIC_READ);
      glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
    }
  }

  void mouseClicked(GLFWwindow *win, int button, int action, int mods) {
    mouseEvent.shouldHandle(win, button, action, mods);
  }

  void handleMouseClickBefore() {
    if (mouseEvent.shouldHandle()) {
      program.setUniform("clickedPosition",
          glm::ivec2((int)mouseEvent.clickedX, (int)mouseEvent.clickedY));
      SSB *d = (SSB *)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
      d->pick_oid = -1;
      d->pick_z = 1000;
      glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    }
  }

  void handleMouseClickAfter() {
    if (mouseEvent.shouldHandle()) {
      SSB *d = (SSB *)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
      std::cout << "Clicked OID: " << d->pick_oid << ", z: " << d->pick_z << std::endl;
      glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
      mouseEvent.clear();
    }
  }

  GLfloat bgcolor[4] = { .1f, .1f, .1f, 1.f };

  virtual void render(double t) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    handleMouseClickBefore();

    program.setUniform("MVP", Projection * View * Model);
    points.get()->render();

    handleMouseClickAfter();
  }
};

GLMAIN(KW8)
