#include "vbosphere.h"
#include "SGP2.hpp"

const int SpherePosition = VBO_attributes::Element + 1;

VBOSphere *theSphere;

SGP2::SGP2(Json *A_, Program *program_, mat4 *P): SG(A_, program_, P) {

  const int slices = stacks * 2;

  { // Sphere vertices and normals

    // nVertices: the number of vertices that form a sphere
    int nVertices = (slices + 1) * (stacks + 1);

    std::unique_ptr<GLfloat[]> vertices(new GLfloat[3 * nVertices]);
    GLfloat *p = vertices.get();

    // 両極は slices 個だけ複製され，左右両端は二つずつ複製されていることに注意
    for (int si = 0; si <= slices; si++) {
      GLfloat theta = (GLfloat) (PI * 2 * si / slices);
      for (int ti = 0; ti <= stacks; ti++) {
        GLfloat phi = (GLfloat)(PI * ti / stacks);
        *p++ = r * sinf(phi) * cosf(theta);
        *p++ = r * sinf(phi) * sinf(theta);
        *p++ = r * cosf(phi);
      }
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo[Vertex]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nVertices, vertices.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(Vertex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Vertex);

    // For the unit sphere, normal vectors happen to be equivalent with vertices vectors
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Normal]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nVertices, vertices.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(Normal, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Normal);
  }

  /* nElements: the number of triangles that form a sphere
     #triangles =
       #(triangles that form the northern fan) +
       #(triangles that form the middle belt area) +
       #(triangles that form the southern fan) */
  nElements = slices + 2 * slices * (stacks - 2) + slices;

  {
    std::unique_ptr<GLuint[]> elements(new GLuint[3 * nElements]);
    GLuint *p = elements.get();

    // インデックスを与えて，element(s) を追加するコード
    const GLuint stackPoints = stacks + 1;
    for (int si = 0; si < slices; si++) {
      GLuint base = si * (stacks + 1);
      for (int ti = 0; ti < stacks; ti++) {
        if (ti != stacks - 1) { // Not the south pole
          *p++ = base + ti;
          *p++ = base + ti + 1;
          *p++ = base + ti + stackPoints + 1;
        }
        if (ti != 0) { // Not the north pole
          *p++ = base + ti + stackPoints + 1;
          *p++ = base + ti + stackPoints;
          *p++ = base + ti;
        }
      }
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[Element]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 3 * nElements, elements.get(), GL_STATIC_DRAW);
  }

  { // Sphere positions
    GLuint vbo;
    glGenBuffers(1, &vbo);
    const float s = (float)(size - 1) / 2;
    //vec3 s2 = vec3(1.f);
    const float s2 = 1.f;

    std::unique_ptr<GLfloat[]> positions(new GLfloat[3 * nSpheres]);
    GLfloat *p = positions.get();
    for (int x = 0; x < size; x++) {
      for (int y = 0; y < size; y++) {
        for (int z = 0; z < size; z++) {
          vec3 v = vec3(x, y, z) / s - s2;
          if (x == 0 && y == 0 && z == 0) cout << "v: " << v << endl;
          *p++ = v.x; *p++ = v.y; *p++ = v.z;
        }
      }
    }

    theSphere = new VBOSphere(1.f, slices, stacks);

    glBindVertexArray(vao);
    //glBindVertexArray(theSphere->getVertexArrayHandle());
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nSpheres, positions.get(), GL_STATIC_DRAW);
    glVertexAttribPointer(SpherePosition, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(SpherePosition);
    glVertexAttribDivisor(SpherePosition, 1);  // Indicates this buffer stores a per-instance attributes
  }
}

void SGP2::render(double t) {
  const mat4 M(1.f);
  const mat4 MV = V * M;
  const mat4 MVP = (*P) * MV;
  program -> setUniform("MV", MV);
  program -> setUniform("MVP", MVP);
  program -> setUniform("Normal", glm::inverseTranspose(mat3(MV)));

  glBindVertexArray(vao);
  glDrawElementsInstanced(GL_TRIANGLES, 3 * nElements, GL_UNSIGNED_INT, nullptr, nSpheres);
}
