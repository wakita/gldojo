/**
 * chap03d1: chap03d.cpp を作成する途中のデバッグ用
 **/

#include <vector>

#include "sngl.hpp"
#include "snshader.hpp"

namespace sn { namespace gl {

class Chapter03D1 : public Application {

  virtual void init() {
    Application::init();
    info.title = "chap03d1: デバッグ用（特に面白みはないです）";
  }

  GLuint rendering_program, vao;

  virtual void startup() {
    rendering_program = program::link(
        shader::load("chap03d1", std::vector<std::string> { ".vs", ".tcs", ".tes", ".fs" }),
        true);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  GLfloat bgcolor[4] = { .2, .2, .2, 1 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);
    glUseProgram(rendering_program);
    glDrawArrays(GL_PATCHES, 0, 3);
  }
};

} } // namespace sn::gl

DECLARE_MAIN(sn::gl::Chapter03D1)
