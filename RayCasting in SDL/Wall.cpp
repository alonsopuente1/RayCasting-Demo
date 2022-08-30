#include "Wall.h"

//Only initialises the vector a and b variables
Wall::Wall(float x1, float y1, float x2, float y2) : a(x1, y1), b(x2, y2) {}

void Wall::Draw(SDL_Renderer* render) {
  //Sets the drawing colour to blue
  SDL_SetRenderDrawColor(render, 0, 0, 255, SDL_ALPHA_OPAQUE);
  //Draws a line from vector a to b
  SDL_RenderDrawLine(render, a.x, a.y, b.x, b.y);
}
