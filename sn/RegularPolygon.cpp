#include "RegularPolygon.hpp"

enum { Position, Normal, Texture, Color, N_VBO = Color + 1 };

RegularPolygon::RegularPolygon(float radius, int nVertices) {
  r = radius;
  n = nVertices;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo[N_VBO]; glGenBuffers(N_VBO, vbo);

  {
    GLfloat position[2 * (n + 1)], *p = position;
    vec4 v0 = vec4(0, r, 0, 1);
    for (int i = 0; i <= n; i++) {
      const float theta = PI * 2 * i / n;
      const float *v = glm::value_ptr(glm::rotateZ(v0, theta));
      *p++ = v[0]; *p++ = v[1];
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Position]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
    glVertexAttribPointer(Position, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Position);
  }

  { // Normal vectors
  }

  { // Texture
  }

  {
    GLfloat color[3 * (n + 1)], *p = color;
    for (int i = 0; i <= n; i++) {
      *p++ = (GLfloat)(cos(PI * 2 * i / n) + 1) / 2;
      *p++ = (GLfloat)(sin(PI * 2 * i / n) + 1) / 2;
      *p++ = .5f;
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Color]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glVertexAttribPointer(Color, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Color);
  }
}

void RegularPolygon::render(double t) const {
  glBindVertexArray(vao);
  if (t < 10)
    for (int i = 0; i < 30*30*30; i++)
      glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLE_FAN, 0, n + 1);
}
