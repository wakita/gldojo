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
      if (clickedX == -1 && clickedY == -1) {
        glfwGetCursorPos(win, &clickedX, &clickedY);
        std::cout << "Clicked position: " << clickedX << ", " << clickedY << std::endl;
      } else {
        std::cerr << "Too frequent mouse clicking.  Sorry, but ignored." << std::endl;
      }
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
  GLuint fsPickWithSSBFunction, fsPaintFunction;
  SSB *ssb;

  virtual void startup() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);

    program.load(A["shaders"], 0);
    program.use();
    program.setUniform("PointSize", A["PointSize"].number_value());
    std::cout << "PointSize: " << A["PointSize"].number_value() << std::endl;
    program.setUniform("Light", glm::normalize(util::vec3(A["WorldLight"])));

    points.reset(new PointGrid(1.f, A["DIM"].int_value()));

    { // Prepare a shader storage buffer
      GLuint ssbo;
      glGenBuffers(1, &ssbo);
      glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
      glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(SSB), nullptr, GL_DYNAMIC_COPY);
      glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
      ssb = (SSB *)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_WRITE);
    }

    {
      fsPickWithSSBFunction =
        glGetSubroutineIndex(program.getHandle(), GL_FRAGMENT_SHADER, "fsPickWithSSBFunction");
      fsPaintFunction =
        glGetSubroutineIndex(program.getHandle(), GL_FRAGMENT_SHADER, "fsPaintFunction");
    }
  }

  void mouseClicked(GLFWwindow *win, int button, int action, int mods) {
    mouseEvent.shouldHandle(win, button, action, mods);
  }

  GLfloat bgcolor[4] = { .1f, .1f, .1f, 1.f };

  virtual void render(double t) {
    if (mouseEvent.shouldHandle()) {
      program.setUniform("clickedPosition", glm::ivec2((int)mouseEvent.clickedX, (int)mouseEvent.clickedY));
      ssb->pick_oid = -1;
      ssb->pick_z = 1000;
      glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &fsPickWithSSBFunction);
    } else {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearBufferfv(GL_COLOR, 0, bgcolor);
      glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &fsPaintFunction);
    }

    program.setUniform("MVP", Projection * View * Model);
    points.get()->render();

    if (mouseEvent.shouldHandle()) {
      glFinish();
      std::cout << "Clicked OID: " << ssb->pick_oid << ", z: " << ssb->pick_z << std::endl;
      mouseEvent.clear();
    }
  }
};

GLMAIN(KW8)
