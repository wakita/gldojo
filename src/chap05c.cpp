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
#include "sngl.hpp"
#include "snshader.hpp"

namespace sn { namespace gl {

class Chapter05C : public Application {
  virtual void init() {
    Application::init();
    info.title = "chap05c: uniformシェーダ変数を利用します";
  }

  enum { vaTime };
  GLuint rendering_program, vao[1];
  GLuint time_loc;

  virtual void startup() {
    rendering_program = program::link(
        shader::load("chap05c", std::vector<std::string> { ".vs", ".fs" }),
        true);

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[vaTime]);

    time_loc = glGetUniformLocation(rendering_program, "time");
  }

  GLfloat bgcolor[4] = { .2, .2, .2, 1 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    glUseProgram(rendering_program);

    glUniform1f(time_loc, t);

    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

} } // namespace sn::gl

DECLARE_MAIN(sn::gl::Chapter05C)
