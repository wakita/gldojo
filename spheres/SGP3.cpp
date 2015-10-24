#include "SGP3.hpp"

SGP3::SGP3(Json *A_, Program *program_, mat4 *P): SG(A_, program_, P) {

  program -> setUniform("PointSize", r);

  { // Vertices
    const float s = (float)(size - 1) / 2, s2 = 1;
    std::unique_ptr<GLfloat[]> vertices(new GLfloat[3 * nSpheres]);
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
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Vertex]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nSpheres, vertices.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(Vertex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Vertex);
  } 

  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

  glBindVertexArray(0);
}

static mat4 M(1);

void SGP3::render(double t) {
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  glm::ivec2 WH(viewport[2], viewport[3]);
  glBindVertexArray(vao);
  program -> setUniform("MVP", (*P) * V * M);
  program -> setUniform("Normal", glm::inverseTranspose(V * M));
  program -> setUniform("WH", WH);
  glDrawArrays(GL_POINTS, 0, nSpheres);
}
