#include "RegularPolygon.hpp"

RegularPolygon::RegularPolygon(float radius, int nVerts) {
  r = radius;
  nVertices = nVerts + 1;

  {
    std::unique_ptr<GLfloat[]> vertices(new GLfloat[2 * nVertices]);
    GLfloat *p = vertices.get();
    *p++ = 0; *p++ = 0;
    vec4 v0 = vec4(0, r, 0, 1);
    for (int i = 0; i < nVerts; i++) {
      const float theta = PI * 2 * i / nVertices;
      const float *v = glm::value_ptr(glm::rotateZ(v0, theta));
      *p++ = v[0]; *p++ = v[1];
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Position]);
    glBufferData(GL_ARRAY_BUFFER, 2 * nVertices, vertices.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(Position, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Position);
  }

  { // Normal vectors
  }

  { // Texture
  }

  {
    std::unique_ptr<GLfloat[]> color(new GLfloat[3 * nVertices]);
    GLfloat *p = color.get();
    *p++ = .5f; *p++ = .5f; *p++ = .5f;
    for (int i = 0; i < nVerts; i++) {
      double t = PI * 2 * i / nVertices;
      *p++ = (GLfloat)(cos(t) + 1) / 2;
      *p++ = (GLfloat)(sin(t) + 1) / 2;
      *p++ = .5f;
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Color]);
    glBufferData(GL_ARRAY_BUFFER, 3 * nVertices, color.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(Color, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Color);
  }
}

void RegularPolygon::render(double t) {
  for (int i = 0; i < (t < 10 ? 30*30*30 : 1); i++)
    glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLE_FAN, 0, nVertices);
}

void RegularPolygon::render() { render(0); }
