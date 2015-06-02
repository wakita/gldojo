/**
 * chap05d: Uniformブロックを利用してデータをシェーダに渡します．
 *
 * https://www.evernote.com/l/AAJ-ksv6ZeBGt5-Nkdy-gmA9REVYAKEAjgE
 **/

#include <cmath>
#include <cstdlib>
#define _DEBUG
#include "Program.hpp"

using namespace smartnova::gl;

class Chapter05D : public Application {

  Program program;

  enum { vaParameter };
  GLuint vao[1], locTime;

  virtual void init() {
    Application::init("chap05d: uniformブロックを利用してデータをシェーダに渡します．");
  }

  GLuint bindingPoint = 0, uBuffer, uIndex;
  GLint uOffset[1];
  struct Parameter { float time; float alpha; };
  struct Parameter params = { 0, 0 };

  virtual void startup() {
    program.load("sb05/sb05d", vector<string> { "vs", "fs" });
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[vaParameter]);

    GLuint _program = program.getHandle();
    uIndex = glGetUniformBlockIndex(_program, "Parameter");
    glUniformBlockBinding(_program, uIndex, bindingPoint);

    glGenBuffers(1, &uBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, uBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(params), &params, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, uBuffer);
  }

  GLfloat bgcolor[4] = { .6, .6, .6, 1 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);
    program.use();

    // Uniform block に設定するデータをバッファに保存
    params.time = t; params.alpha = (sin(t) + 1) / 2;
    // Uniform block にデータを設定．今回はいいのだけれども，uniform block が
    // あるときに，ブロックを指定する方法が不明．
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(params), &params);

    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

DECLARE_MAIN(Chapter05D)
