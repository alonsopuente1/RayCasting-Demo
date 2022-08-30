#pragma once

//These are included to have less clutter in other header files
#include <iostream>
#include <ctime>
#include "Vector.h"
#include <vector>
#include <SDL.h>
#include "Ray.h"
#include "Wall.h"

//Used for debugging mostly, shorter than having to type the whole thing out again and again
#define LOG(x) std::cout << x << std::endl

//Exact value of pi
#define PI acos(-1)

//Short for field of view. The higher, the wider the view is
#define FOV 90

//Title of the window
#define TITLE "RayCasting"

//Frames per second. How many times the application is refreshed a second
#define FPS 60

//No need to explain this
#define FULLSCREEN false

//The "map" is just a top down view of what is happening in the simulation, set to true to see what I mean
#define SHOWMAP false

//How fast the player rotates, increase to rotate faster
#define ROTATESPEED 0.5
//How fast the player moves, increase to move faster
#define MOVESPEED 2

//Enables fish-eye effect when true
#define FISHEYE false

//Turn this to true to use your mouse to rotate. I would turn this off as this doesn't work too well
#define MOUSEMOVEMENT true

//Initial direction that the player is facing
#define INITDIR PI / 2

//If it is fullscreen, width and height are set to fit the entire screen, change this if your have a higher or lower resolution screen
#if FULLSCREEN == true

//Width of the screen
#define WIDTH 1920
//Height of the screen
#define HEIGHT 1080

//Else just set it to a smaller window
#else

//Width of the screen
#define WIDTH 1280
//Height of the screen
#define HEIGHT 720

#endif

//How many rays the player draws, defaulted to width. The higher this number is, the smoother, however decreased performance
#define RESOLUTION WIDTH

// Turns degrees to radians
float radians(float deg);

// Returns a random number from 0 to upper bound, excluding the upper bound number itself
float random(int ub);

//If lb is greater than upper bound, it returns 0
float random(int lb, int ub);

// Distance from one point to another
float dist(float x1, float y1, float x2, float y2);

// Distance from one vector to another
float dist(Vector a, Vector b);

// Draws a rectangle on the screen with the origin being the center, providing the renderer
void rect(SDL_Renderer* render, float x, float y, float w, float h);

// Maps a value from one range to another. Used when calculating brightness and height of rectangles of simulation
float map(float value, float min1, float max1, float min2, float max2);

// Adds a rectangle as an array of walls. Very useful to make the map different, only used in Application class
void AddRect(std::vector<Wall>* walls, float x, float y, float w, float h);
