#include "Point.hpp"

Point::Point(GLfloat r) {
  { // Positions
    std::unique_ptr<GLfloat[]> positions(new GLfloat[4]);
    GLfloat *p = positions.get();
    p[0] = p[1] = p[2] = 0;
    p[3] = r;
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Position]);
    glBufferData(GL_ARRAY_BUFFER, 4, positions.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(Position, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Position);
  }
}

void Point::render(double t) {
  glBindVertexArray(vao);
  glPatchParameteri(GL_PATCH_VERTICES, 1);
  glDrawArrays(GL_PATCHES, 0, 1);
}

void Point::render() { render(0); }
