#include "Vector.h"
#include <math.h>

Vector::Vector()
{
  x = 0;
  y = 0;
}

Vector::Vector(float x, float y)
{
  this->x = x;
  this->y = y;
}

void Vector::Add(Vector a)
{
  x += a.x;
  y += a.y;
}

void Vector::Add(float x, float y)
{
  this->x += x;
  this->y += y;
}

void Vector::Add(float a)
{
  x += a;
  y += a;
}

void Vector::Sub(Vector a)
{
  x -= a.x;
  y -= a.y;
}

void Vector::Sub(float x, float y)
{
  this->x -= x;
  this->y -= y;
}

void Vector::Sub(float a)
{
  x -= a;
  y -= a;
}

void Vector::Div(Vector a)
{
  x /= a.x;
  y /= a.y;
}

void Vector::Div(float x, float y)
{
  this->x /= x;
  this->y /= y;
}

void Vector::Div(float a)
{
  x /= a;
  y /= a;
}

void Vector::Mult(Vector a)
{
  x *= a.x;
  y *= a.y;
}

void Vector::Mult(float x, float y)
{
  this->x *= x;
  this->y *= y;
}

void Vector::Mult(float a)
{
  x *= a;
  y *= a;
}

float Vector::Mag() {
  return sqrt((x * x) + (y * y));
}

void Vector::SetMag(float mag) {
  const float magRatio = mag / Mag();
  x *= magRatio;
  y *= magRatio;
}

void Vector::Set(float x, float y) {
  this->x = x;
  this->y = y;
}

float Vector::Ang() {
  return atan(y / x);
}
