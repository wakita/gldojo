#include "sngl.hpp"

namespace sn { namespace gl {

class AppTest : public Application {
  void init() {
    Application::init();
    info.title = std::string("OpenGL App Framework Test");
  }

  void start() { }

  virtual void render(double currentTime) {
    static const GLfloat red[] = { 1.f, 0.f, 0.f, 1.f };
    glClearBufferfv(GL_COLOR, 0, red);
  }
};

}; }; // namespace sn::gl::

DECLARE_MAIN(sn::gl::AppTest)
