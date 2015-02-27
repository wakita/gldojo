#include "Program.hpp"

using namespace smartnova::gl;

class GLFWtest : public Application {
  virtual void init() {
    Application::init("GLFW Simple Example");
  }

  int width, height;
  float ratio;
  virtual void startup() {
    glfwGetFramebufferSize(window, &width, &height);
    Check;
    ratio = width / (float)height;
  }

  virtual void render(double t) {
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glRotatef((float)t * 50, .0f, .0f, 1.f);  // the angle is given in Degree

    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.2f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, -0.2f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0, 0.6f, 0.0f);
    glEnd();
  }
};

DECLARE_MAIN(GLFWtest)
