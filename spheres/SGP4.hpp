#pragma once

#include "Volume.hpp"

class SGP4: public Volume {
  private:
    GLfloat r;

  public:
    SGP4(GLfloat, int);
    virtual void render(double);
    virtual void render();
};
