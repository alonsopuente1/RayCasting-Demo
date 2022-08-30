#pragma once

#include "Utilities.h"
#include "Wall.h"

class Ray
{

public:
  //Constructor for ray, takes a position and starting angle to be facing
  Ray(Vector pos, float ang);

  //This is used to update the position to the parameter passed through, used to update the rays so that they are on the player at all times
  void Update(Vector pos);
  //This rotates the ray by adding to the direction variable, also to update the rays so that it is in line with the players direction
  void Rotate(float ang);
  //This draws a line from the position to pointOfCollision, if there isnt a point of collision, it draws a line in the direction the ray is looking at
  void Draw(SDL_Renderer* render);
  //This is what updates the rays pointOfCollision and returns the distance from the ray to the pointOfCollision
  float Check(std::vector<Wall> walls);

  //Direction of the ray
  float p_dir;
  //Position of the ray
  Vector p_pos;

  //This is updated in Check, true if a wall has been hit, false if it hit nothing
  bool p_hit;

  //This stores the index of the wall that was hit by the ray. This is used to add "lighting" depending on the position of the ray to the wall
  int p_wallHitIndex;

private:
  //Position of where the ray collided with a wall, if there was a collision
  Vector m_pointOfCollision;

};

