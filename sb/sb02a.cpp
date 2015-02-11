/**
 * ウィンドウを表示し中を赤で消去する例．
 **/

#include "sngl.hpp"

namespace sn { namespace gl {
using sn::gl::Application;

class Chapter02A : public Application {
  virtual void init() {
    Application::init();
    info.title = "chap02a: ウィンドウを赤で消去";
  }

  virtual void render(double t) {
    static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, red);
  }
};

} }

DECLARE_MAIN(sn::gl::Chapter02A)
