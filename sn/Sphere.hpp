#pragma once

#include "Volume.hpp"

class Sphere : public Volume {
  private:
    GLuint radius_, slices_, stacks_;
    void generateVolume(const GLfloat*, const GLfloat*, const GLfloat*, const GLfloat*);

  public:
    Sphere(float, int, int);
    virtual void render(double);
    virtual void render();
};
