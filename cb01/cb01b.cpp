// Debugging APIの利用方法

#include "Program.hpp"

using namespace smartnova::gl;

const float positions[] = {
  -0.8f, -0.8f,  0.0f,
   0.8f, -0.8f,  0.0f,
   0.0f,  0.8f,  0.0f };

const float colors[] = {
   1.0f,  0.0f,  0.0f,
   0.0f,  1.0f,  0.0f,
   0.0f,  0.0f,  1.0f };

class CB01B : public Application {
  virtual void init() {
    Application::init("cb01b: Basic Scene (デバッグ機能，トレース機能)");
  }

  Program program;
  GLuint vao;
  enum { Position, Color, N_VBO = Color + 1 };
  
  virtual void startup() {
    program.load("cb01/cb01", vector<string> { "vs", "fs" });
    program.use();

    // Create and set-up the vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo[N_VBO];
    glGenBuffers(N_VBO, vbo);

    // トレース機能の利用
    setTrace(true);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Position]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Position);
    setTrace(false);

    // Populate the Color buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Color]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Color);

    // デバッグ情報の出力
    notify("Initialization is complete!");
  }

  virtual void render(double t) {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

DECLARE_MAIN(CB01B)

