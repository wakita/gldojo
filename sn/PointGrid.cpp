#include "PointGrid.hpp"

PointGrid::PointGrid(float radius, int dim) {
  r = radius;
  nVertices = dim * dim * dim;

  { // Vertices
    std::cout << "#vertices = " << nVertices << std::endl;
    const float s = (float)(dim - 1) / 2, s2 = 1;
    std::unique_ptr<GLfloat[]> vertices(new GLfloat[3 * nVertices]);
    GLfloat *p = vertices.get();
    for (int x = 0; x < dim; x++) {
      for (int y = 0; y < dim; y++) {
        for (int z = 0; z < dim; z++) {
          *p++ = x / s - s2;
          *p++ = y / s - s2;
          *p++ = z / s - s2;
        }
      }
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Vertex]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nVertices, vertices.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(Vertex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Vertex);
  }
  
  { // Normal vectors
  }

  { // Texture
  }

  { // Color
  }

  glBindVertexArray(0);
}

void PointGrid::render(double t) {
  glBindVertexArray(vao);
  glPointSize(r);
  glDrawArrays(GL_POINTS, 0, nVertices);
}

void PointGrid::render() { render(0); }
