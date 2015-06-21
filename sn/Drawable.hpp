#pragma once

#include "Program.hpp"

class Drawable {
  public:
    Drawable();

    virtual void render(double) const = 0;
};
