#include <stdlib.h>

#include "Program.hpp"

using namespace smartnova::gl;

class GlewTest : public Application {
  virtual void init() {
    info.flags.visible = 0;
    Application::init(string("OpenGL GLEW Test"));
  }

  virtual void startup() {
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;
  }

  virtual void render(double t) {
    exit(EXIT_SUCCESS);
  }
};

DECLARE_MAIN(GlewTest)
