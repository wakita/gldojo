#pragma once

#include "SG.hpp"

class SGP3: public SG {
  public:
    SGP3(Json *, Program *, mat4 *);
    virtual void render(double);
};
