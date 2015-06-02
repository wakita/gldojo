/**
 * chap03a: シェーダにデータを送る
 *
 * 三角形が円周上を移動するアニメーション．
 *
 * 三角形の形状は vs が持っているが，そのオフセット (offset) をアプリケーションから
 * 与えることによってアニメーションを実現している．座標は四元数だが，このアプリケーション
 * から与えるオフセット値は offset = { x, y } だけである．これを vs のなかで四元数に
 * 拡張している．
 **/

#include <cmath>

#define _DEBUG
#include "Program.hpp"

using namespace smartnova::gl;

class Chapter03AX : public Application {

  virtual void init() {
    Application::init("chap03a: シェーダーへのデータの送信");
  }

  enum { vaOffset = 0 };
  GLuint vao[1];
  Program program;

  virtual void startup() {
    program.load("sb03/sb03a", vector<string>{ "vs", "fs" });

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[vaOffset]);
  }

  GLfloat bgcolor[4] = { .2, .2, 0, 1 };
  GLfloat offset [2] = { 0, 0 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    program.use();

    offset[0] = (float)(sin(t) * 0.5);
    offset[1] = (float)(cos(t) * 0.5);
    glVertexAttrib4fv(vaOffset, offset);

    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

DECLARE_MAIN(Chapter03AX)
