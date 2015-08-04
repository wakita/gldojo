#include "SGP4.hpp"

SGP4::SGP4(GLfloat radius, int size) {
  r = radius;
  nVertices = size * size * size;

  { // Positions
    std::cout << "#vertices = " << nVertices << std::endl;
    const float s = (float)(size - 1) / 2, s2 = 1;
    std::unique_ptr<GLfloat[]> vertices(new GLfloat[3 * nVertices]);
    GLfloat *p = vertices.get();
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < size; y++) {
        for (int z = 0; z < size; z++) {
          *p++ = x / s - s2;
          *p++ = y / s - s2;
          *p++ = z / s - s2;
        }
      }
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Position]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nVertices, vertices.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(Position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Position);
  }

  glBindVertexArray(0);
}

void SGP4::render(double t) {
  glBindVertexArray(vao);
  glPointSize(r);
  glDrawArrays(GL_POINTS, 0, nVertices);
}

void SGP4::render() { render(0); }
