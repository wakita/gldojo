#include "RegularPolygon.hpp"

RegularPolygon::RegularPolygon(float radius, int nVerts) {
  r = radius;
  nVertices = nVerts + 3;

  {
    std::unique_ptr<GLfloat[]> vertices(new GLfloat[2 * nVertices]);
    GLfloat *p = vertices.get();
    *p++ = 0; *p++ = 0;
    vec4 v0 = vec4(0, r, 0, 1);
    for (int i = 0; i <= nVerts; i++) {
      const GLfloat theta = PI * 2 * i / nVerts;
      const GLfloat *v = glm::value_ptr(glm::rotateZ(v0, theta));
      *p++ = v[0]; *p++ = v[1];
    }
    *p++ = 0; *p++ = 0;
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Position]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * nVertices, vertices.get(), GL_STATIC_DRAW);
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
    *p++ = 0.2; *p++ = 0.2; *p++ = 0.2;
    for (int i = 0; i < 3 * (nVerts + 1); i++) *p++ = 1;
    *p++ = 0.2; *p++ = 0.2; *p++ = 0.2;
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Color]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nVertices, color.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(Color, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Color);
  }
}

void RegularPolygon::render(double t) {
  glDrawArrays(GL_TRIANGLE_FAN, 0, nVertices);
}

void RegularPolygon::render() { render(0); }
