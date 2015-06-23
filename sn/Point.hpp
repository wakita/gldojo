#pragma once

#include "Volume.hpp"

class Point : public Volume {
  public:
    Point(float r);
    virtual void render(double);
    virtual void render();
};
