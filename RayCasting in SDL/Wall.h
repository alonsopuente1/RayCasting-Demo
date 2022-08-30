#pragma once

#include <SDL.h>
#include "Vector.h"

class Wall
{
public:
  //Constructor takes has 4 parameters that set the two vectors a and b
  Wall(float x1, float y1, float x2, float y2);

  //Draws a line on the screen from vector a to b. This is only called in the player object when SHOWMAP is true
  void Draw(SDL_Renderer* render);

  //The two vectors a and b. These are only used in the ray's check function
  Vector a;
  Vector b;
};

