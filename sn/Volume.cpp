#include "Volume.hpp"

Volume::Volume() {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(N_VBO, vbo);
}
