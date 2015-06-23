#include "Sphere.hpp"

Sphere::Sphere(float radius, int slices, int stacks) :
  radius_(radius), slices_(slices), stacks_(stacks) {

    nVertices = (slices + 1) * (stacks + 1);
    nElements = (slices * 2 * (stacks - 1)) * 3;

    const std::unique_ptr<GLfloat[]> vertices(new GLfloat[3 * nVertices]);
    const std::unique_ptr<GLfloat[]> normals(new GLfloat[3 * nVertices]);
    const std::unique_ptr<GLfloat[]> texcoords(new GLfloat[2 * nVertices]);
    const std::unique_ptr<GLfloat[]> elements(new GLfloat[nElements]);

    generateVolume(vertices.get(), normals.get(), texcoords.get(), elements.get());
}

void Sphere::generateVolume(
    const GLfloat *vertices,
    const GLfloat *normals,
    const GLfloat *texcoords,
    const GLfloat *elements) {
}

void Sphere::render(double t) {
  glBindVertexArray(vao);
}

void Sphere::render() { render(0); }
