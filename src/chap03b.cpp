/**
 * chap03b: 複数のデータをシェーダに送る
 *
 * 三角形のアニメーション (chap03a) で色も変化させる．
 *
 * データを fs に直接，送ることはできない．そこで，まず vs にオフセットに加えて，
 * 色のデータも送り，vs はその色を fs に転送する．
 *
 * ※ 送信するデータごとに vertex array object (VAO) を利用することに注意．
 * ※ 配列渡しの glVertexAttrib*fv ではなく，値渡しの glVertexAttrib*f を用いている．
 **/

#include <cmath>
#include <vector>
#define _DEBUG
#include "sngl.hpp"
#include "snshader.hpp"

namespace sn { namespace gl {

class Chapter03B : public Application {

  virtual void init() {
    Application::init();
    info.title = "chap03b: 複数の値をシェーダに送る";
  }

  GLuint rendering_program, vao[1];
  enum { vaOffset, vaColor };

  virtual void startup() {
    rendering_program = program::link(
        shader::load(
          "/Users/wakita/Dropbox (smartnova)/work/opengl/glsb6/media/shaders/chap03b",
          std::vector<std::string> { ".vs", ".fs" }),
        true);

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[vaOffset]);
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

DECLARE_MAIN(sn::gl::Chapter03B)
