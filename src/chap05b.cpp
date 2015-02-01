/**
 * chap05b: 構造体の配列をシェーダに渡す例です．（未完）
 *
 * 本来は chap05a と同じものになるはずなのですが，どこかにバグがあるようでうまく
 * 配列のデータがシェーダに渡っていないようです．青い背景が見えるだけでグラデーションの
 * かかった三角形が表示されません．トホホ．
 *
 * この例では，データの構造体 (vertex_data) を宣言し，その配列によって三角形の各頂点の
 * 座標と色のデータ (vdata) を用意し，それをシェーダにまとめて送ろうとしています．この
 * ときに，受け取る vs 側は二つの変数 position と color で受け取ろうとしているので，
 * 適宜，構造体の中身に分けてやらなくてはなりません．このために，構造体の表現を分析し
 * それにしたがってデータを送るようにしています．
 *
 * 原因が不明なのですが，うまく動いていません．以前は動いていたような気がするのに．．．
 **/

#include <cmath>
#include <vector>
#define _DEBUG
#include <sngl.hpp>
#include <snshader.hpp>

namespace sn { namespace gl {

class Chapter05B : public Application {

  virtual void init() {
    Application::init();
    info.title = "構造体の配列をシェーダに渡す例です．でもバグってます．";
  }

  struct vertex_data {
    float x, y, z;  // Position
    float r, g, b;  // Color
  };

  enum { vaPosition, vaColor };
  enum { bufVertex };
  GLuint rendering_program, vao[2], buffers[1];

  virtual void startup() {
    rendering_program = program::link(
        shader::load(
          "/Users/wakita/Dropbox (smartnova)/work/opengl/glsb6/media/shaders/chap05b",
          std::vector<std::string> { ".vs", ".fs" }),
        true);

    glGenVertexArrays(2, vao);
    glBindVertexArray(vao[vaPosition]);
    glBindVertexArray(vao[vaColor]);

    const vertex_data vdata[3] = {
      {  0.25, -0.25,  0.5,  1.0,  0.0,  0.0 },
      { -0.25, -0.25,  0.5,  0.0,  1.0,  0.0 },
      {  0.0,   0.25,  0.5,  0.0,  0.0,  1.0 } };

    glBindBuffer(GL_ARRAY_BUFFER, buffers[bufVertex]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vdata), vdata, GL_STATIC_DRAW);

    glVertexAttribPointer(vaPosition,
        3, GL_FLOAT, GL_FALSE, sizeof(vertex_data),
        (void*)offsetof(vertex_data, x));
    glEnableVertexAttribArray(vaPosition);

    glVertexAttribPointer(vaColor,
        3, GL_FLOAT, GL_FALSE, sizeof(vertex_data),
        (void*)offsetof(vertex_data, r));
    glEnableVertexAttribArray(vaColor);
  }

  GLfloat bgcolor[4] = { .2, .2, 0, 1 };

  virtual void render(double t) {
    bgcolor[2] = (float)(sin(t) + 1) / 2;
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    glUseProgram(rendering_program);

    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

} } // namespace sn::gl

DECLARE_MAIN(sn::gl::Chapter05B)
