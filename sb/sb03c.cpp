/**
 * chap03c: Interface Block の利用
 *
 * アプリケーションの内容は chap03b.cpp とほぼ同じ．シェーダの書き方だけが異なる．
 *
 * 今回は vs から fs に受け渡すデータの記述に Inferface Block を用いた．これを用いる
 * ことで関連する複数のデータをひとまとめに扱うとともに，異なるシェーダから見える同じ
 * データに異なる命名をすることができる．
 **/

#include <cmath>
#include <vector>
#define _DEBUG
#include "sngl.hpp"
#include "snshader.hpp"

namespace sn { namespace gl {

class Chapter03C : public Application {
  virtual void init() {
    Application::init();
    info.title = "chap03c: Interface Block の利用";
  }

  enum { vaOffset, vaColor };
  GLuint rendering_program, vao[2];

  virtual void startup() {
    rendering_program = program::link(
        shader::load("chap03c", std::vector<std::string> { ".vs", ".fs" }),
        true);

    glGenVertexArrays(2, vao);
    glBindVertexArray(vao[vaOffset]);
    glBindVertexArray(vao[vaColor]);
  }

  GLfloat bgcolor[4] = { .2, .2, .2, 1 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    glUseProgram(rendering_program);

    glVertexAttrib2f(vaOffset, sin(t) / 2, cos(t) / 2);
    glVertexAttrib4f(vaColor, (sin(t) + 1) / 2, (cos(t) + 1) / 2, 0, 1);

    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

} }

DECLARE_MAIN(sn::gl::Chapter03C)
