#pragma once

#include "Program.hpp"

enum VBO_attributes { Position, Normal, Texture, Color, N_VBO = Color + 1 };

class Volume {
  protected:
    GLuint vao;
    GLuint vbo[N_VBO];
    int nVertices, nElements;

  public:
    Volume();

    virtual void render() = 0;
};
