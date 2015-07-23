#pragma once

#include "Volume.hpp"

class PointGrid: public Volume {
  private:
    float r;

  public:
    PointGrid(float, int);
    virtual void render(double);
    virtual void render();
};
