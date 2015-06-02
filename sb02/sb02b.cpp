/**
 * ウィンドウの背景色を時間とともに変化させる例
 **/

#include "Program.hpp"

using namespace smartnova::gl;

class Chapter02BX : public Application {
  virtual void init() {
    Application::init(string("chap02b: 背景色を変化させる"));
  }

  virtual void startup() {}

  GLfloat c[4] = { 0, 0, 0, 1 };

  virtual void render(double t) {
    c[0] = (float)(sin(t)/2 + 0.5);
    c[1] = (float)(cos(t)/2 + 0.5);
    glClearBufferfv(GL_COLOR, 0, c);
  }
};

DECLARE_MAIN(Chapter02BX)
