#define _DEBUG
#include "Program.hpp"

// using namespace smartnova::gl;

class AppTest : public smartnova::gl::Application {
  virtual void init() {
    Application::init(string("OpenGL App Framework Test"));
  }

  virtual void startup() {
    cerr << "I am running on " << SYSTEM_NAME << endl;

    cerr << "Viewport setting...";
    //glViewport(0, 0, info.winWidth, info.winHeight);
    cerr << "  done." << endl;

    cerr << "Depth test seting...";
    glEnable(GL_DEPTH_TEST);
    cerr << "  done." << endl;
  }

  const GLfloat bgcolor[4] = { 1.f, 0.f, 0.f, 1.f };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);
    glClearColor(1.f, 0.f, 0.f, 1.f);
  }
};

DECLARE_MAIN(AppTest)
