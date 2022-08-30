#include "Application.h"

/*

RayCasting Demo made with the SDL2 library in C++

See "Utilities.h" for more options on FOV, rotation speed, movement speed and more.

For more explanation on how this works and
all the classes made and used, go to any file and see
comments made on nearly every line of code.

Author: Alonso Puente
Date Created: 15/08/2022 20:15:01
Last Edit Timestamp: 25/08/2022 22:41

*/

int main(int argc, char* argv[]) {
  //Create application object
  Application app;

  //Call Loop function
  app.Loop();

  return 0;
}
