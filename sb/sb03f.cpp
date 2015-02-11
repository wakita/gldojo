#include <cmath>
#define _DEBUG
#include "sngl.hpp"
#include "snshader.hpp"

namespace sn { namespace gl {

class Chapter03F : public Application {

  virtual void init() {
    Application::init();
    info.title = "Fragmentシェーダを用いて位置に依存した彩色をします．";
  }

  enum { vaOffset, vaColor };
  GLuint rendering_program, vao[2];

  virtual void startup() {
    rendering_program = program::link(
        shader::load("chap03f",
          std::vector<std::string> { ".vs", ".tcs", ".tes", ".gs", ".fs" }),
        true);

    glGenVertexArrays(2, vao);
    glBindVertexArray(vao[vaOffset]);
    glBindVertexArray(vao[vaColor]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPointSize(30);
  }

  GLfloat bgcolor[4] = { 0, 0, 0, 0 };

  virtual void render(double t) {
    double s = sin(t), c = cos(t);
    bgcolor[0] = (float)(s + 1) / 2;
    bgcolor[1] = (float)(c + 1) / 2;
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    glVertexAttrib2f(vaOffset, (float)s / 2, (float)c / 2);
    glVertexAttrib4f(vaColor, bgcolor[1], bgcolor[0], .3f, 1.f);

    glUseProgram(rendering_program);
    glDrawArrays(GL_PATCHES, 0, 3);
  }
};

} } // namespace sn::gl

DECLARE_MAIN(sn::gl::Chapter03F)
