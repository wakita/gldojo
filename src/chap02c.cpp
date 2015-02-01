/**
 * ごく簡単なシェーダーの利用
 * vs: 与えられた座標にそのまま描画し，fsのために色を指定する．
 * fs: vsから指定された色を出力
 *
 * シェーダを利用するために vertex array object (vao) を用いていることに注意．
 *
 * 中央に青い正方形が見える．これは実際にはペンの太さを40ptで描画した点です．
 * 正方形の色は，fsが決めたものをvsに渡しています．
 * 背景色は時間に応じて変化させています．
 **/

#include <cmath>
#include <vector>

#define _DEBUG
#include "sngl.hpp"
#include "snshader.hpp"

namespace sn { namespace gl {

class Chapter02C : public Application {
  virtual void init() {
    Application::init();
    info.title = "chap02c: 初めてのシェーダ";
  }

  GLuint rendering_program;

  virtual void startup() {
    rendering_program = program::link(
        shader::load(
          "/Users/wakita/Dropbox (smartnova)/work/opengl/glsb6/media/shaders/",
          std::vector<std::string> { "chap02c.vs", "chap02c.fs" }),
        true);

    GLuint vao[1];
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
  }

  GLfloat color[4] = { 0, 0, 0, 1 };

  virtual void render(double t) {
    color[0] = (float)(sin(t)/2 + 0.5);
    color[1] = (float)(cos(t)/2 + 0.5);
    glClearBufferfv(GL_COLOR, 0, color);

    glUseProgram(rendering_program);
    glPointSize(40.f);
    glDrawArrays(GL_POINTS, 0, 1);
  }
};
} } // namespace sn::gl

DECLARE_MAIN(sn::gl::Chapter02C)
