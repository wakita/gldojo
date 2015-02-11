/**
 * chap03g: ts があるときに vs から fs へデータを送ってみる（未完）
 *
 * 普通にやるとうまくいきません．tcs と fs が以下のようなエラーを出力します．少し
 * tcs や tes をいじったのですが，うまくいきません．
 *
 * WARNING: Output of vertex shader 'vs_color' not read by tessellation control shader
 * ERROR: Input of fragment shader 'vs_color' not written by tessellation evaluation
 * shader
 **/

#include <cmath>
#define _DEBUG
#include "sngl.hpp"
#include "snshader.hpp"

namespace sn { namespace gl {

class Chapter03G : public Application {
  virtual void init() {
    Application::init();
    info.title = "chap03g: （バグ）vs-fs 間に別のシェーダが挟まるとデータを送れない．．．";
  }

  enum { vaOffset };
  GLuint rendering_program, vao[1];

  virtual void startup() {
    rendering_program = program::link(
        shader::load("chap03g",
          std::vector<std::string> { ".vs", ".tcs", ".tes", ".fs" }),
        true);
    
    glGenVertexArrays(2, vao);
    glBindVertexArray(vao[vaOffset]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPointSize(5);
  }

  GLfloat bgcolor[4] = { 0, 0, 0, 0 };

  virtual void render(double t) {
    double s = sin(t), c = cos(t);

    bgcolor[0] = (float)(s * .4 + .4);
    bgcolor[1] = (float)(c * .4 + .4);
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    glVertexAttrib2f(vaOffset, (float)(s * .5), (float)(c * .6));

    glUseProgram(rendering_program);
    glDrawArrays(GL_PATCHES, 0, 3);
  }
};

} } // namespace sn::gl

DECLARE_MAIN(sn::gl::Chapter03G)
