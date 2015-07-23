#include "Program.hpp"
#include "Utility.hpp"
#include "PointGrid.hpp"

using std::cout;
using std::endl;

using glm::radians;
using glm::rotate;
using glm::translate;

using namespace smartnova;
using namespace smartnova::gl;

int D, N;

class MouseClickEvent {
  public:
    double x = -1, y = -1;
};

class KW6: public Application {
  public: KW6(Json config): Application(config) {}

  mat4 Model, View;
  vec3 LookEye, LookAt, LookUp;

  virtual void init() {
    Application::init();

    D = A["dim"].int_value();
    N = D * D * D;

    { Json Look = A["Look"];
      LookEye = util::vec3(Look["eye"]);
      LookAt  = util::vec3(Look["at"]);
      LookUp  = util::vec3(Look["up"]);
    }

    Model = mat4(1);
  }

  enum { POS };
  Program program;
  unique_ptr<PointGrid> points;

  virtual void startup() {
    program.load(A["shaders"], 0);
    program.use();
    program.setUniform("pointSize", A["pointSize"].number_value());
    program.setUniform("Light", glm::normalize(util::vec3(A["WorldLight"])));

    points.reset(new PointGrid(1.f, D));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_CLIP_PLANE0);
  }

  void onResize(GLFWwindow *win, int w, int h) {
    std::cout << "onResize" << std::endl;
    info.winWidth = w; info.winHeight = h;
    glViewport(0, 0, w, h);
    Projection = glm::perspective(glm::radians(70.0f), (float)w/h, 0.1f, 100.0f);
  }

  MouseClickEvent clickEv;

  void mouseClicked(GLFWwindow *win, int button, int action, int mods) {
    cout << "Mouse clicked" << endl;
    glfwGetCursorPos(win, &clickEv.x, &clickEv.y);
  }

  void mousePressed(GLFWwindow *win, int button, int action, int mods) {
    cout << "Mouse pressed" << endl;
  }

  void mouseReleased(GLFWwindow *win, int button, int action, int mods) {
    cout << "Mouse released" << endl;
  }

  void mouseDragged(GLFWwindow *win, int xpos, int ypos) {
    cout << "Mouse dragged @(" << xpos << ", " << ypos << ")" << endl;
  }

  void mouseMoved(GLFWwindow *win, int xpos, int ypos) {
    cout << "Mouse moved @(" << xpos << ", " << ypos << ")" << endl;
  }

  bool pressing = false, dragging = false;
  void onMouseButton(GLFWwindow *win, int button, int action, int mods) {
    if (action == GLFW_RELEASE) {
      mouseReleased(win, button, action, mods);
      if (!dragging) mouseClicked(win, button, action, mods);
      pressing = dragging = false;
    } else if (action == GLFW_PRESS && !pressing) {
      mousePressed(win, button, action, mods);
      pressing = true;
    } else {
      std::cerr << "Unknown mouse operation (" << action << ")" << std::endl;
    }
  }

  void onCursorPos(GLFWwindow *win, double xpos, double ypos) {
    if (pressing) mouseDragged(win, xpos, ypos);
    else mouseMoved(win, xpos, ypos);
  }

  GLfloat bgcolor[4] = { .1f, .1f, .1f, 1.f };

  virtual void render(double t) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    View = lookAt(rotate(LookEye, (GLfloat)(PI * (.9 - t / 20)), Y), LookAt, LookUp);

    program.setUniform("t",   (GLfloat)t);
    program.setUniform("MVP", Projection * View * Model);

    points.get()->render();
  }
};

GLMAIN(KW6)
