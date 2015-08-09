#pragma once

#include "Program.hpp"

enum VBO_attributes { Vertex, Normal, Texture, Color, Element, N_VBO = Element + 1 };

class Volume {
  protected:
    GLuint vao;
    GLuint vbo[N_VBO];
    int nVertices, nElements;

  public:
    Volume();

    virtual void render() = 0;
};
