/**
 * chap03e: Geometry シェーダを追加しました．Geometryシェーダは，Tessallation シェーダ
 * から与えられた図形を他の図形に変換する働きを持ちます．この例では，三角形をその頂点で
 * 置き換えています．
 **/

#include <cmath>
#define _DEBUG
#include "Program.hpp"

using namespace smartnova::gl;

class Chapter03EX : public Application {
  virtual void init() {
    Application::init("chap03e: Geometryシェーダを追加");
  }

  enum { vaOffset, vaColor };
  GLuint vao[2];
  Program program;

  virtual void startup() {
    program.load("sb03/sb03e", vector<string>{ "vs", "tcs", "tes", "geom", "fs" });

    glGenVertexArrays(2, vao);
    glBindVertexArray(vao[vaOffset]);
    glBindVertexArray(vao[vaColor]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPointSize(5);
  }

  GLfloat bgcolor[4] = { 0, 0, 0, 0 };
  GLfloat offset[2];

  virtual void render(double t) {
    double s = sin(t), c = cos(t);
    bgcolor[0] = s * .4 + .4;
    bgcolor[1] = c * .4 + .4;

    glClearBufferfv(GL_COLOR, 0, bgcolor);
    program.use();

    glVertexAttrib2f(vaOffset, s / 2, c / 2);
    glVertexAttrib1f(vaColor, (s + 1) / 2);

    glDrawArrays(GL_PATCHES, 0, 3);
  }
};

DECLARE_MAIN(Chapter03EX)
