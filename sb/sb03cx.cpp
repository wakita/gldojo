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

#define _DEBUG
#include "Program.hpp"

using namespace smartnova::gl;

class Chapter03CX : public Application {
  virtual void init() {
    Application::init("chap03c: Interface Block の利用");
  }

  enum { vaOffset, vaColor };
  GLuint vao[2];
  Program program;

  virtual void startup() {
    program.load("sb03c", vector<string>{ "vs", "fs" });

    glGenVertexArrays(2, vao);
    glBindVertexArray(vao[vaOffset]);
    glBindVertexArray(vao[vaColor]);
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

DECLARE_MAIN(Chapter03CX)
