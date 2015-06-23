#pragma once

#include "Volume.hpp"

class Point : public Volume {
  private:
    float r;

  public:
    Point();
    virtual void render(double);
    virtual void render();
};
