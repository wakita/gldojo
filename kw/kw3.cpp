#include <fstream>

#include "Program.hpp"
#include "Utility.hpp"
#include "RegularPolygon.hpp"

using namespace smartnova::gl;

class KW3 : public Application {

  public:
    KW3(json11::Json config): Application(config) {}

    virtual void init() {
      info.flags.vsync = 1;
      Application::init();
    }

    virtual void startup() {
      Program program;
      program.load(A["shaders"], 0);
      program.use();

      GLuint vao; glGenVertexArrays(1, &vao); glBindVertexArray(vao);
      GLuint vbo; glGenBuffers(1, &vbo);

      GLfloat point[] = { -1.f, -1.f, 1.f, -1.f, 1.f, 1.f, -1.f, 1.f };
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

      glEnableVertexAttribArray(0);
    }

    GLfloat bgcolor[4] = { 0, 0, 0, 1 };

    virtual void render(double t) {
      glClearBufferfv(GL_COLOR, 0, bgcolor);
      glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

      GLubyte d[sizeof(GLuint) * 256], *p = d;
      glReadPixels(0, 0, 256, 1, GL_RGBA, GL_UNSIGNED_BYTE, d);
      for (int X = 0; X < 256; X++) {
        GLuint r = *p++, g = *p++, b = *p++, a = *p++;
        GLint x = (r << 8) | g, y = (b << 8) | a;

        std::cout << "X: " << X << ", xy: " << x << ", " << y << std::endl;
        assert(x == X); assert(y == 0);
      }
      glfwSetWindowShouldClose(Window.get(), true);
    }
};

GLMAIN(KW3)
