#include <cmath>
#define _DEBUG
#include "Program.hpp"

using namespace smartnova::gl;

class Chapter03F : public Application {

  virtual void init() {
    Application::init("Fragmentシェーダを用いて位置に依存した彩色をします．");
  }

  enum { vaOffset, vaColor };
  GLuint vao[2];
  Program program;

  virtual void startup() {
    program.load("sb03f", vector<string>{ "vs", "tcs", "tes", "geom", "fs" });

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

    program.use();
    glDrawArrays(GL_PATCHES, 0, 3);
  }
};

DECLARE_MAIN(Chapter03F)
