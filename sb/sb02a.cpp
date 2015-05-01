/**
 * ウィンドウを表示し中を赤で消去する例．
 **/

#include "Program.hpp"

using namespace smartnova::gl;

class Chapter02AX : public Application {
  virtual void init() {
    Application::init(string("chap02a: ウィンドウを赤で消去"));
  }

  virtual void startup() {}

  GLfloat bgcolor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

  virtual void render(double t) {
    glClearBufferfv(GL_COLOR, 0, bgcolor);
  }
};

DECLARE_MAIN(Chapter02AX)
