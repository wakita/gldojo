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

#define _DEBUG
#include "Program.hpp"

using namespace smartnova::gl;

class Chapter03BX : public Application {

  virtual void init() {
    Application::init("chap03b: 複数の値をシェーダに送る");
  }

  GLuint vao[1];
  enum { vaOffset, vaColor };
  Program program;

  virtual void startup() {
    auto exts = vector<string>{ "vs", "fs" };
    program.load("sb03b", exts);

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[vaOffset]);
  }

  GLfloat bgcolor[4] = { .2, .2, .2, 1 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    program.use();

    glVertexAttrib2f(vaOffset, sin(t) / 2, cos(t) / 2);
    glVertexAttrib4f(vaColor, (sin(t) + 1) / 2, (cos(t) + 1) / 2, 0, 1);

    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

DECLARE_MAIN(Chapter03BX)
