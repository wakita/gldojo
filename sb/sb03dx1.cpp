/**
 * Tessallation 処理を追加しました．Tessallation 処理は，与えられた図形を再帰的に細分化
 * する処理です．Tessallation 処理の効果がはっきりとするように，三角形は線画で描画
 * しています．
 *
 * Tessallation 処理の記述には，Tessallation Control Shader (TCS) と Tessallation
 * Evalution Shader (TES) を用います．アプリケーションの記述は二つのシェーダの読み込み
 * 以外は基本的に同じです．
 **/

#include <cmath>

#define _DEBUG
#include "Program.hpp"

using namespace smartnova::gl;

class Chapter03DX : public Application {
  virtual void init() {
    Application::init("chap03d: Tessallationシェーダの導入");
  }

  enum { vaOffset, vaColor };
  GLuint vao[2];
  Program program;

  virtual void startup() {
    program.load("sb03d1", vector<string>{ "vs", "tcs", "tes", "fs" });

    glGenVertexArrays(2, vao);
    glBindVertexArray(vao[vaOffset]);
    glBindVertexArray(vao[vaColor]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  GLfloat bgcolor[4] = { .2, .2, .2, 1 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    program.use();

    glVertexAttrib2f(vaOffset, sin(t) / 2, cos(t) / 2);
    glVertexAttrib4f(vaColor, (sin(t) + 1) / 2, (cos(t) + 1) / 2, 0, 1);

    glDrawArrays(GL_PATCHES, 0, 3);
  }
};

DECLARE_MAIN(Chapter03DX)
