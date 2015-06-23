#include "Point.hpp"

Point::Point() {

  {
    std::unique_ptr<GLfloat[]> position(new GLfloat[2]);
    GLfloat *p = position.get();
    *p++ = 0; *p++ = 0;
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Position]);
    glBufferData(GL_ARRAY_BUFFER, 2, position.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(Position, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Position);
  }
}

void Point::render(double t) {
  glBindVertexArray(vao);
  glPatchParameteri(GL_PATCH_VERTICES, 1);
  glDrawArrays(GL_PATCHES, 0, 1);
}

void Point::render() { render(0); }
