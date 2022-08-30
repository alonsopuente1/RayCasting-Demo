#pragma once

#include "Utilities.h"

class Player
{
public:
  //Two parameters for the starting position of the player
  Player(float x, float y);
  //This draws the visualisation of the rays that are casted, if SHOWMAP is true, this draws the player, the walls and the player itself
  void Draw(SDL_Renderer* render);
  //This rotates the player and rays with the parameter passed through, used for rotating when the mouse moves. Also moves the playing forward or backward depending on the p_wPressed and p_sPressed variables
  void Update(float mouseX);

  //If one of these is true, the player moves forwards or backwards
  bool p_wPressed;
  bool p_sPressed;

  //If one of these is true, the player strafes left or right
  bool p_aPressed;
  bool p_dPressed;

  bool p_raPressed;
  bool p_laPressed;

  //This sets the private variable m_walls to the variable passed through, used in the application constructor
  void InitWalls(std::vector<Wall> walls);

private:
  //Angle that the player is facing, in radians
  float m_dir;
  //Position of the player
  Vector m_pos;

  //Array of walls in the map, used for checking collision in "Ray.h"
  std::vector<Wall> m_walls;
  //Array of Ray objects to check collision for any wall in m_walls
  std::vector<Ray> m_rays;
  //Used for checking collision between the player and walls in the map
  std::vector<SDL_FRect> m_wallRect;
  //Used for drawing the rectangles, refreshing each time the player moves storing an array of floats which is the distance between the player and collision of each ray on a wall respectively
  std::vector<float> m_scene;

  //This rotates the player by whatever is passed through the parameter
  void Rotate(float ang);
  //This moves the player forwards or backwards depending on if the number is passed through is negative or not
  void Move(float dir);
  //A negative number makes the player move left, a positive number makes the player move right
  void Strafe(float dir);
  //Collision checks based on a velocity
  void Collision(Vector offset);

  void RotateRays(float ang);
  void UpdateRaysPos();
};

