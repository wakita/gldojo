#include "SG.hpp"

SG::SG(Json *A_, Program *program_, mat4 *P_) {
  A = A_;
  program = program_;

  size = (*A)["SIZE"].int_value();
  nSpheres = size * size * size;

  stacks = (*A)["STACKS"].int_value();

  r = (*A)["PointSize"].number_value();

  { Json Look = (*A)["Look"];
    V = lookAt(util::vec3(Look["eye"]), util::vec3(Look["at"]), util::vec3(Look["up"])); }

  P = P_;

  program -> setUniforms("Light",    (*A)["Light"]);
  program -> setUniforms("Material", (*A)["Material"]);
}

void SG::render(double t) {}
void SG::render() { this -> render(0); }
