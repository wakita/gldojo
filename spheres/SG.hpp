#pragma once

#include "Volume.hpp"
#include "Utility.hpp"

using namespace json11;
using namespace smartnova;
using namespace smartnova::gl;

class SG: public Volume {
  protected:
    Json *A;
    Program *program;
    int size;
    GLuint stacks;
    int nSpheres;
    GLfloat r;
    mat4 V, *P;

  public:
    SG(Json *, Program *, mat4 *);
    virtual void render(double);
    virtual void render();
};
