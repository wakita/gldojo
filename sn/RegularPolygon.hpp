#pragma once

#include "Drawable.hpp"

class RegularPolygon : public Drawable {
  private:
    unsigned int vao;
    float r;
    int n;

  public:
    RegularPolygon(float, int);
    void render(double) const;
};
