#include "SG.hpp"

SG::SG(Json *A_, Program *program_, mat4 *P) {
  A = A_;
  program = program_;
  r = (*A)["PointSize"].number_value();
  size = (*A)["SIZE"].int_value();
  stacks = (*A)["STACKS"].int_value();
  nSpheres = size * size * size;
  Projection = P;
}

void SG::render(double t) {}
void SG::render() { this -> render(0); }
