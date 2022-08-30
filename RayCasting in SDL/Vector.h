#pragma once

/*
* Vector class to store x and y variable.
* Also with functions that have 3 overloads to vary what
* you want to do with the Vector
*/

class Vector
{
public:
  float x;
  float y;

  //If no parameters are passed, it defaults the x and y to 0
  Vector();
  //Else set x and y to what is passed through
  Vector(float x, float y);

  //These functions are self explanatory, different overloads depending on the situation
  void Add(Vector a);
  void Add(float x, float y);
  void Add(float a);

  void Sub(Vector a);
  void Sub(float x, float y);
  void Sub(float a);

  void Div(Vector a);
  void Div(float x, float y);
  void Div(float a);

  void Mult(Vector a);
  void Mult(float x, float y);
  void Mult(float a);

  //Returns magnitude of this vector
  float Mag();

  //Sets magnitude of this vector to whatever is passed through
  void SetMag(float mag);

  //Sets x and y of this vector to whatever is passed through. This is useful to not have two lines setting the x and the y, but instead have one line setting it in a function
  void Set(float x, float y);

  //Returns angle of this vector. Not used in this project but might be useful in others
  float Ang();
};
