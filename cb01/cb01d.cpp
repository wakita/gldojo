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

class CB01D : public Application {
  virtual void init() {
    Application::init("cb01d: Basic Scene (Uniformを名前でバインド，トレース機能)");
  }

  Program program;
  enum { Position, Color, N_VBO = Color + 1 };
  GLuint locRotationMatrix;
  
  virtual void startup() {
    program.load("cb01/cb01d", vector<string> { "vs", "fs" });
    program.use();

    program.printActiveAttribs();

    // Create and set-up the vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo[N_VBO];
    glGenBuffers(N_VBO, vbo);

    // Populate the Position buffer object
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

    locRotationMatrix = program.uniformLocation("RotationMatrix");
  }

  float angle = 0.f;

  virtual void render(double t) {
    glClear(GL_COLOR_BUFFER_BIT);

    mat4 rotationMatrix = glm::rotate(mat4(1.f), (float)t, vec3(0.f, 0.f, 1.f));
    glUniformMatrix4fv(locRotationMatrix, 1, GL_FALSE, &rotationMatrix[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

DECLARE_MAIN(CB01D)
