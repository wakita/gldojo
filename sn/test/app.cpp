#define _DEBUG
#include "Program.hpp"

using namespace smartnova::gl;

class AppTest : public Application {
  virtual void init() {
    Application::init(string("OpenGL App Framework Test"));
  }

  virtual void startup() {
    cout << "SYSTEM_NAME: " << SYSTEM_NAME << endl;
    cout << "I am running on " <<
#   if defined(OS_Darwin)
      "OSX"
#   elif defined(OS_Linux)
      "Linux"
#   elif defined(OS_Windows)
      "Windows"
#   endif
      << endl;
  }

  const GLfloat bgcolor[4] = { 1.f, 0.f, 0.f, 1.f };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);
  }
};

DECLARE_MAIN(AppTest)
