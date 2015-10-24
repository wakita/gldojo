#pragma once

#include "SG.hpp"

class SGP4: public SG {
  public:
    SGP4(Json *, Program *, mat4 *);
    virtual void render(double);
};
