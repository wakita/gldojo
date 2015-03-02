/**
 * chap05c: uniformシェーダ変数を利用します．
 *
 * シェーダの uniform データについて確認してみます．uniform データはすべての
 * シェーダで共通に見える仕掛けとなっています．
 *
 * このプログラムは，三角形が周回するデモですが，その大きさを周期的に変化させ，
 * さらに時間の経過とともに黒かった三角形に色みが増すように工夫しています．
 *
 * 実装にあたっては開始からの経過時間を uniform として保存しています．この値を
 * vs と fs が参照し，それぞれ三角形の大きさと色みの計算に利用しています．
 **/

#include <cmath>
#define _DEBUG
#include "Program.hpp"

using namespace smartnova::gl;

class Chapter05C : public Application {
  virtual void init() {
    Application::init("chap05c: uniform変数を利用してデータをシェーダに渡します．");
  }

  enum { vaTime };
  GLuint vao[1];
  GLuint locTime;
  Program program;

  virtual void startup() {
    program.load("sb05c", vector<string> { "vs", "fs" });

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[vaTime]);

    //locTime = glGetUniformLocation(rendering_program, "time");
    locTime = program.uniformLocation("time");
  }

  GLfloat bgcolor[4] = { .2, .2, .2, 1 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    program.use();

    glUniform1f(locTime, t);

    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

DECLARE_MAIN(Chapter05C)
