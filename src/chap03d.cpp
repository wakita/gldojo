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
#include <vector>
#define _DEBUG
#include "sngl.hpp"
#include "snshader.hpp"

namespace sn { namespace gl {

class Chapter03D : public Application {

  virtual void init() {
    Application::init();
    info.title = "chap03d: Tessallationシェーダの導入";
  }

  enum { vaOffset, vaColor };
  GLuint rendering_program, vao[2];

  virtual void startup() {
    rendering_program = program::link(
        shader::load(
          "/Users/wakita/Dropbox (smartnova)/work/opengl/glsb6/media/shaders/chap03d",
          std::vector<std::string> { ".vs", ".tcs", ".tes", ".fs" }),
        true);

    glGenVertexArrays(2, vao);
    glBindVertexArray(vao[vaOffset]);
    glBindVertexArray(vao[vaColor]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  GLfloat bgcolor[4] = { .2, .2, .2, 1 };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);

    glUseProgram(rendering_program);

    glVertexAttrib2f(vaOffset, sin(t) / 2, cos(t) / 2);
    glVertexAttrib4f(vaColor, (sin(t) + 1) / 2, (cos(t) + 1) / 2, 0, 1);

    glDrawArrays(GL_PATCHES, 0, 3);
  }
};

} } // namespace sn::gl

DECLARE_MAIN(sn::gl::Chapter03D)
