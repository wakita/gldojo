#pragma once

#include "Volume.hpp"
#include "Utility.hpp"

using namespace json11;
using namespace smartnova;
using namespace smartnova::gl;

class SG: public Volume {
  protected:
    mat4 *Model, *View, *Projection;
    Json *A;
    Program *program;
    GLfloat r;
    GLuint size;
    GLuint stacks;
    int nSpheres;

  public:
    SG(Json *, Program *, mat4 *);
    virtual void render(double);
    virtual void render();
};
