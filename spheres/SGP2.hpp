#pragma once

#include "SG.hpp"

class SGP2: public SG {
  public:
    SGP2(Json *, Program *, mat4 *);
    virtual void render(double);
};
