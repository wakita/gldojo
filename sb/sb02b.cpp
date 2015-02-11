/**
 * ウィンドウの背景色を時間とともに変化させる例
 **/

#include <cmath>
#include "sngl.hpp"

namespace sn { namespace gl {
class Chapter02B : public Application {
  virtual void init() {
    Application::init();
    info.title = "chap02b: 背景色を変化させる";
  }

  GLfloat c[4] = { 0, 0, 0, 1 };

  void render(double t) {
    c[0] = (float)(sin(t)/2 + 0.5);
    c[1] = (float)(cos(t)/2 + 0.5);
    glClearBufferfv(GL_COLOR, 0, c);
  }
};
} }

DECLARE_MAIN(sn::gl::Chapter02B)
