#include "Utilities.h"


float radians(float deg) {
  return ( PI / 180 ) * deg;
}

float random(int ub) {
  return rand() % ub;
}

float random(int lb, int ub) {
  if (lb > ub)
    return 0;

  return rand() % (ub - lb) + lb;
}

float dist(float x1, float y1, float x2, float y2) {
  x2 -= x1;
  y2 -= y1;

  return sqrt((x2 * x2) + (y2 * y2));
}

float dist(Vector a, Vector b) {
  float x = b.x - a.x;
  float y = b.y - a.y;

  return sqrt((x * x) + (y * y));
}

void rect(SDL_Renderer* render, float x, float y, float w, float h) {
  x -= w / 2;
  y -= h / 2;

  SDL_FRect rect = { x, y, w, h };

  SDL_RenderFillRectF(render, &rect);
}

float map(float value, float min1, float max1, float min2, float max2) {
  max1 -= min1;
  max2 -= min2;

  float ratio = value / max1;

  return max2 * ratio + min2;
}

void AddRect(std::vector<Wall>* walls, float x, float y, float w, float h) {
  walls->push_back(Wall(x, y, x + w, y));
  walls->push_back(Wall(x + w, y, x + w, y + h));
  walls->push_back(Wall(x + w, y + h, x, y + h));
  walls->push_back(Wall(x, y + h, x, y));
}

