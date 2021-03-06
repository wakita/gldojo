/**
 * chap05a: アプリケーションから vs にデータを送り込む例です．
 *
 * 3章までの例では，図形の座標はシェーダに定数として書き込んでいました．ここでは，
 * アプリケーションからシェーダにデータを送り込みます．このためにバッファというもの
 * を利用します．
 *
 * ここでは，三角形の各頂点の座標と色を与えるために，それぞれにバッファを用意しています．
 **/

#include <cmath>
#define _DEBUG
#include <Program.hpp>

using namespace smartnova::gl;

class Chapter05A : public Application {

  virtual void init() {
    Application::init("chap05a: アプリから vs にデータを送り込む例です");
  }

  enum { vaData };
  enum { bufPosition, bufColors };
  GLuint vao[1], buffers[2];
  Program program;

  virtual void startup() {
    program.load("sb05/sb05a", vector<string>{ "vs", "fs" });

    // MacBook Air では，VAOを初期化しなくても動いていたような気がしたけれど
    // iMac5K では以下がないと動かない．
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[vaData]);

    glGenBuffers(2, buffers);

    const GLfloat triangle_vertices[4*3] = {
      0.25, -0.25,  0.5, 1.0,
     -0.25, -0.25,  0.5, 1.0,
      0.0,   0.25,  0.5, 1.0 };

    glBindBuffer(GL_ARRAY_BUFFER, buffers[bufPosition]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices,
        GL_STATIC_DRAW);
    glVertexAttribPointer(bufPosition, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(bufPosition);

    const GLfloat triangle_colors[4*3] = {
      1.0, 0.0, 0.0, 1.0,
      0.0, 1.0, 0.0, 1.0,
      0.0, 0.0, 1.0, 1.0 };

    glBindBuffer(GL_ARRAY_BUFFER, buffers[bufColors]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_colors), triangle_colors,
        GL_STATIC_DRAW);
    glVertexAttribPointer(bufColors, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(bufColors);
  }

  GLfloat bgcolor[4] = { 0, 0, 0, 1};

  virtual void render(double t) {
    bgcolor[0] = bgcolor[1] = bgcolor[2] = (float)(sin(t) * .5 + .5);
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    program.use();
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

DECLARE_MAIN(Chapter05A)
