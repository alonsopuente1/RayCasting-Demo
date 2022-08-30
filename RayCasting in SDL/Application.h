#pragma once

#include "Player.h"
#include "Utilities.h"

//This class is where everything gets run and the SDL window and renderer objects are made.
class Application
{
public:
  //Constructor for the object, does not take parameters as width height and title are defined in "Utilities.h"
  Application();

  //Destructor for the object, destroys renderer and window
  ~Application();

  //Main Loop
  void Loop();
private:
  //SDL window object, this is the actual window itself, if this is destroyed, the entire application stops working
  SDL_Window* m_window;
  //SDL renderer object, this is where all the graphics are drawn
  SDL_Renderer* m_render;

  //HandleEvents handles key presses to move the player forward and backward
  void HandleEvents();
  //Update handles mouse movement (if enabled) to rotate the player and updates the player
  void Update();
  //Draws the rectangles to the screen + the "ceiling" and "floor"
  void Draw();

  //The player object itself, which is explained further in "Player.cpp"
  Player m_player;

  //This variable is the variable that keeps the program running, if this is false, the program stops
  bool m_loop;
};

