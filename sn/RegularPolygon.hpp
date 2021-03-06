#pragma once

#include "Volume.hpp"

class RegularPolygon : public Volume {
  private:
    float r;

  public:
    RegularPolygon(float, int);
    virtual void render(double);
    virtual void render();
};
