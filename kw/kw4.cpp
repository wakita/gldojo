#include <fstream>

#include "Program.hpp"
#include "Utility.hpp"
#include "RegularPolygon.hpp"

using namespace smartnova::gl;

typedef unsigned int uint;

class KW4 : public Application {
  GLuint BITS, SCALE;

  public:
    KW4(json11::Json config): Application(config) {}

    virtual void init() {
      info.flags.vsync = 1;
      Application::init();
      BITS = A["bits"].int_value();
      SCALE = 1 << BITS;
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

      GLuint buffer; glGenBuffers(1, &buffer);
      glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffer);
      glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(GLuint) * SCALE * SCALE, NULL, GL_DYNAMIC_DRAW);

      glEnableVertexAttribArray(0);
    }

    GLfloat bgcolor[4] = { 0, 0, 0, 1 };

    bool done = false;

    const uint MASK = (1 << 23) - 1;

    virtual void render(double t) {
      glClearBufferfv(GL_COLOR, 0, bgcolor);
      glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

      if (!done) {
        GLfloat d[SCALE * SCALE];
        uint v[SCALE * SCALE];
        glReadPixels(0, 0, SCALE, SCALE, GL_RED, GL_FLOAT, d);
        for (int x = 0; x < SCALE; x++) {
          for (int y = 0; y < SCALE; y++) {
            int p = y * SCALE + x;
            uint fr = *(reinterpret_cast<uint *>(d + p));
            v[p] = fr & MASK;
          }
        }
        std::ofstream ofs("x.dat");
        for (int id = 0; id < SCALE * SCALE; id++) {
          ofs << std::dec << id << " " << std::hex << buffer[id] << std::endl;
          // ofs << std::dec << id << " " << std::hex << v[id] << std::endl;
        }
        ofs.close();
        done = true;
      }
    }
};

GLMAIN(KW4)
