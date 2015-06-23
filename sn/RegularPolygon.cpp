#include "RegularPolygon.hpp"

RegularPolygon::RegularPolygon(float radius, int nVerts) {
  r = radius;
  nVertices = nVerts;

  {
    std::unique_ptr<GLfloat[]> position(new GLfloat[2 * (nVertices + 1)]);
    GLfloat *p = position.get();
    vec4 v0 = vec4(0, r, 0, 1);
    for (int i = 0; i <= nVertices; i++) {
      const float theta = PI * 2 * i / nVertices;
      const float *v = glm::value_ptr(glm::rotateZ(v0, theta));
      *p++ = v[0]; *p++ = v[1];
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Position]);
    glBufferData(GL_ARRAY_BUFFER, 2 * (nVertices + 1), position.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(Position, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Position);
  }

  { // Normal vectors
  }

  { // Texture
  }

  {
    std::unique_ptr<GLfloat[]> color(new GLfloat[3 * (nVertices + 1)]);
    GLfloat *p = color.get();
    for (int i = 0; i <= nVertices; i++) {
      *p++ = (GLfloat)(cos(PI * 2 * i / nVertices) + 1) / 2;
      *p++ = (GLfloat)(sin(PI * 2 * i / nVertices) + 1) / 2;
      *p++ = .5f;
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Color]);
    glBufferData(GL_ARRAY_BUFFER, 3 * (nVertices + 1), color.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(Color, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Color);
  }
}

void RegularPolygon::render(double t) {
  if (t < 10)
    for (int i = 0; i < 30*30*30; i++)
      glBindVertexArray(vao);
  else glBindVertexArray(vao);

  glDrawArrays(GL_TRIANGLE_FAN, 0, nVertices + 1);
}

void RegularPolygon::render() { render(0); }
