#include "Program.hpp"
#include "Utility.hpp"
#include "RegularPolygon.hpp"

using namespace smartnova::gl;

class KW3 : public Application {
  GLuint BITS, SCALE, MASK;

  public:
    KW3(json11::Json config): Application(config) {}

    virtual void init() {
      info.flags.vsync = 1;
      Application::init();
      BITS = A["bits"].int_value();
      SCALE = 1 << BITS;
      MASK = SCALE - 1;
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

      program.setUniform("BITS",    BITS);

      glEnableVertexAttribArray(0);
    }

    GLfloat bgcolor[4] = { 0, 0, 0, 1 };

    virtual void render(double t) {
      glClearBufferfv(GL_COLOR, 0, bgcolor);
      glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

      GLfloat d[4 * SCALE * SCALE];
      glReadPixels(0, 0, SCALE, SCALE, GL_RGBA, GL_FLOAT, d);
      for (int curX = 0; curX < SCALE; curX++) {
        for (int curY = 0; curY < SCALE; curY++) {
          int p = 4 * (curY * SCALE + curX);
          GLfloat fr = d[p + 0], fg = d[p + 1], fb = d[p + 2], fa = d[p + 3];
          GLuint r, g, b, a;
          GLuint x, y, z;

          switch (FAILURE) {
            case 0:
              r = (GLuint)(SCALE * fr); g = (GLuint)(SCALE * fg);
              b = (GLuint)(SCALE * fb); a = (GLuint)(SCALE * fa);
              x = (r << BITS) + g; y = (b << BITS) + a;
              break;

            case 1:
              r = glm::floatBitsToInt(fr);
              g = glm::floatBitsToInt(fg);
              b = glm::floatBitsToInt(fb);
              a = glm::floatBitsToInt(fa);
              break;
          }

          std::cout <<
            glm::uvec2(curX, curY) <<
            ", xy: " << glm::uvec2(x, y) <<
            ", Δ: " << glm::uvec2(x - curX, y - curY) << std::endl;
        }
      }
      glfwSetWindowShouldClose(Window.get(), true);
    }
};

GLMAIN(KW3)
