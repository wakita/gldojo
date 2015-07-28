#include <fstream>

#include "Program.hpp"
#include "Utility.hpp"
#include "RegularPolygon.hpp"

using namespace smartnova::gl;

using std::cout;
using std::endl;

const int PIXELS = 1024 * 1024;
GLuint d[sizeof(GLuint) * PIXELS];

class KW5 : public Application {

  public:
    KW5(json11::Json config): Application(config) {}

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

      GLuint *p = d;
      glReadPixels(0, 0, 1024, 1024, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, d);
      for (int Y = 0; Y < 1024; Y++) {
        for (int X = 0; X < 1024; X++) {
          GLuint c = *p++, r, g, b, a;
          r = (c >> 24) & 255;
          g = (c >> 16) & 255;
          b = (c >> 8) & 255;
          a = c & 255;

          int x = (r << 8) | g, y = (b << 8) | a;

          assert(x == X); assert(y == Y);
        }
      }
      cout << "All the assertion test have passed successfully." << endl;
      glfwSetWindowShouldClose(Window.get(), true);
    }
};

GLMAIN(KW5)
