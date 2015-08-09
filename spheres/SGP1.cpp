#include "SGP1.hpp"

GLfloat r;
int size;
mat4 V;

SGP1::SGP1(Json *A_, Program *program_, mat4 *P):
  SG(A_, program_, P) {

  const int slices = stacks * 2;

  Json APP = *A;

  r = APP["PointSize"].number_value();

  { Json Look = APP["Look"];
    V = lookAt(util::vec3(Look["eye"]), util::vec3(Look["at"]), util::vec3(Look["up"])); }

  program -> setUniforms("Light",    APP["Light"]);
  program -> setUniforms("Material", APP["Material"]);

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
        *p++ = sinf(phi) * cosf(theta);
        *p++ = sinf(phi) * sinf(theta);
        *p++ = cosf(phi);
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
    glVertexAttribPointer(Element, 3, GL_UNSIGNED_INT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(Element);
  }

  glBindVertexArray(vao);
}

bool reported = false;

void SGP1::render(double t) {
  glBindVertexArray(vao);

  const mat4 ID(1.f);
  const mat4 Scale = glm::scale(ID, glm::vec3(r));
  mat4 P = *Projection;

  if (!reported) {
    cout << "Scale: " << Scale << endl;
    reported = true;
  }

  const float s = (float)(size - 1) / 2;
  vec3 s2 = vec3(1.f);
  for (int x = 0; x < size; x++) {
    for (int y = 0; y < size; y++) {
      for (int z = 0; z < size; z++) {
        // glm::mat4 M = glm::translate(Scale, glm::vec3(x / s - s2, y / s - s2, z / s - s2));
        //mat4 M = translate(Scale, vec3(x, y, z) / s - s2);
        // mat4 M = scale(translate(ID, vec3(x, y, z) / s - s2), glm::vec3(r));
        // mat4 M = Scale * translate(ID, vec3(x, y, z) / s - s2);
        // mat4 M = translate(Scale, vec3(x, y, z) / s - s2);
        mat4 M = translate(ID, vec3(x, y, z) / s - s2) * Scale;
        mat4 MV = V * M;
        program -> setUniform("MV", MV);
        program -> setUniform("MVP", P * MV);
        program -> setUniform("Normal", glm::inverseTranspose(mat3(MV)));
        glDrawElements(GL_TRIANGLES, 3 * nElements, GL_UNSIGNED_INT, nullptr);
      }
    }
  }
}
