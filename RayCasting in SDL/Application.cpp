#include "Application.h"

Application::Application() : m_player(50, 50) {
  //Reset random seed to get different results each time (if the random() function is used)
  srand((unsigned)time(0));


  //Create window with title, width and height variables declared in "Utilities.h"
    
  //If fullscreen is true, include fullscreen SDL flag to make the window fullscreen
  if (FULLSCREEN)
    m_window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
  //Else create the window without SDL flags
  else
    m_window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

  //Load BMP image in source files
  SDL_Surface* icon = SDL_LoadBMP("icon.bmp");

  //Set the window icon
  SDL_SetWindowIcon(m_window, icon);

  //Free the icon surface
  SDL_FreeSurface(icon);

  //Create the renderer from the window. This is where all the graphics are drawn
  m_render = SDL_CreateRenderer(m_window, -1, 0);

  //Set loop to true
  m_loop = true;

  //Create temporary walls array to add to the player object after
  std::vector<Wall> tempWalls;

  //Create walls around the screen
  AddRect(&tempWalls, 1, 1, WIDTH - 1, HEIGHT - 1);

  //Create the map itself

  //First parameter is the array of walls, passed by reference to actually add the walls to the array 
  //Second and third parameters are the x and y of the rectangle
  //Last two parameters are the width and height of the rectangle

  //If you want to create a map yourself, you can use this function to add some walls in different places if you want to

  AddRect(&tempWalls, random(WIDTH), random(HEIGHT), 100, 100);
  AddRect(&tempWalls, random(WIDTH), random(HEIGHT), 100, 100);
  AddRect(&tempWalls, random(WIDTH), random(HEIGHT), 100, 100);
  AddRect(&tempWalls, random(WIDTH), random(HEIGHT), 100, 100);

  //If mouse movement is on, hide the cursor. Change parameter to SDL_ENABLE to show the cursor
  if(MOUSEMOVEMENT)
    SDL_ShowCursor(SDL_DISABLE);

  //Add walls to the private variable in the player object, goto "Player.cpp" to see more
  m_player.InitWalls(tempWalls);
}

Application::~Application() {
  //Destroy the window and renderer and quit SDL
  SDL_DestroyWindow(m_window);
  SDL_DestroyRenderer(m_render);
  SDL_Quit();
}

void Application::Loop() {
  //While the m_loop variable is true, handle events, update and draw
  while (m_loop) {
    //Delay the program by 1 second divided by the FPS variable declared in "Utilities.h"
    SDL_Delay(1000 / FPS);

    //Handle any key presses first then update the player and mouse and then draw
    HandleEvents();
    Update();
    Draw();
  }
}

void Application::HandleEvents() {
  //Create SDL_Event variable
  SDL_Event event;

  //While there are events
  while (SDL_PollEvent(&event) > 0) {
    switch (event.type) {

      //If the x button is pressed when the window is in windowed mode, turn loop to false
    case SDL_QUIT:
      m_loop = false;
      return;
    }

    //Only do the next part of this code if a key is pressed or released. 
    if (!(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP))
      continue;

    //Get a snapshot of the current keys state
    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    //If escape is pressed, set loop to false and return
    if (keys[SDL_SCANCODE_ESCAPE] == 1) {
      m_loop = false; return;
    }

    //If w is pressed, set w pressed to true in the player variable
    if (keys[SDL_SCANCODE_W] == 1)
      m_player.p_wPressed = true;
    //Else set it to false
    else
      m_player.p_wPressed = false;

    //Repeat this for keys s, a, d, left arrow and right arrow

    if (keys[SDL_SCANCODE_S] == 1)
      m_player.p_sPressed = true;
    else
      m_player.p_sPressed = false;

    if (keys[SDL_SCANCODE_A] == 1)
      m_player.p_aPressed = true;
    else
      m_player.p_aPressed = false;

    if (keys[SDL_SCANCODE_D] == 1)
      m_player.p_dPressed = true;
    else
      m_player.p_dPressed = false;

    if (keys[SDL_SCANCODE_RIGHT] == 1)
      m_player.p_raPressed = true;
    else
      m_player.p_raPressed = false;

    if (keys[SDL_SCANCODE_LEFT] == 1)
      m_player.p_laPressed = true;
    else
      m_player.p_laPressed = false;
  }
}

void Application::Update() {
  //If mouse movement is disabled, skip the rest of this function
  if (!MOUSEMOVEMENT) {
    m_player.Update(0);
    return;
  }
  
  //Get current mouse position and store it in a vector
  int x, y;
  SDL_GetMouseState(&x, &y);

  Vector mousePos(x, y);

  //Set mouse position to the middle of the screen, if the mouse is in the screen
  if (SDL_GetMouseFocus() == m_window)
    SDL_WarpMouseInWindow(m_window, WIDTH / 2, HEIGHT / 2);

  //Get difference of the mouse position
  mousePos.Sub(WIDTH / 2, HEIGHT / 2);

  //Update player with the different in the x, in radians. This is to rotate the player as the Rotate function is private in the player object
  m_player.Update(radians(mousePos.x * (ROTATESPEED / 3)));
}

void Application::Draw() {
  //Set the drawing colour to black
  SDL_SetRenderDrawColor(m_render, 0, 0, 0, SDL_ALPHA_OPAQUE);

  //Clear the screen to make it fully black
  SDL_RenderClear(m_render);

  //Gradient from white to black from the top of the screen to the midddle and the bottom of the screen to the middle
  for (int i = 0; i < HEIGHT / 2; i++)
  {
    //Map i to colour from range 70 - 0. This means the lower the i, the brighter
    float mappedColour = map(i, 0, HEIGHT / 2, 70, 0);
    //Create an FRect with a height of 1 that strectches across the entire screem
    SDL_FRect rect = { 0, i, WIDTH, 1 };
    //Set the drawing colour to the mapped colour
    SDL_SetRenderDrawColor(m_render, mappedColour, mappedColour, mappedColour, SDL_ALPHA_OPAQUE);
    //Draw the FRect we created earlier
    SDL_RenderDrawRectF(m_render, &rect);

    //From flip the y to go from the bottom
    rect.y = HEIGHT - i;

    //Draw the rect again
    SDL_RenderDrawRectF(m_render, &rect);
  }

  //Call the draw function in the player object and pass the renderer variable through the function
  m_player.Draw(m_render);

  //After all of this, present the renderer
  SDL_RenderPresent(m_render);
}
