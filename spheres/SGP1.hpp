#pragma once

#include "SG.hpp"

class SGP1: public SG {
  public:
    SGP1(Json *, Program *, mat4 *);
    virtual void render(double);
};
