#include "Ray.h"

Ray::Ray(Vector pos, float ang) : 
  //Initialise position and pointOfCollision vector variables
  p_pos(pos.x, pos.y), 
  
  //This sets the point of collision 10 pixels away in the angle that is passed through the constructor
  m_pointOfCollision(cos(ang) * 10 + pos.x, sin(ang) * 10 + pos.y) {
  
  //Sets this direction to angle passed through
  p_dir = ang;

  //Sets hit to false at first
  p_hit = false;
}

void Ray::Update(Vector pos) {
  //Updates position vector to the vector that is passed through
  p_pos = pos;
}

void Ray::Rotate(float ang) {
  //Adds angle to the current direction
  p_dir += ang;
}

void Ray::Draw(SDL_Renderer* render) {
  //This function is called if SHOWMAP is true

  //If the ray didn't any walls hit, set the colour to red
  if (!p_hit)
    SDL_SetRenderDrawColor(render, 255, 0, 0, SDL_ALPHA_OPAQUE);
  //Else set the colour to green
  else
    SDL_SetRenderDrawColor(render, 0, 255, 0, SDL_ALPHA_OPAQUE);

  //Draws a line to the point of collision
  SDL_RenderDrawLine(render, p_pos.x, p_pos.y, m_pointOfCollision.x, m_pointOfCollision.y);
}

float Ray::Check(std::vector<Wall> walls) {
  //Creates a vector which stores where the direction is facing
  Vector dirVec(cos(p_dir), sin(p_dir));
  //Record vector to keep track of the closest wall a ray has hit
  Vector record;

  //At first, hit is false
  p_hit = false;

  //Variables for the line-line intersection algorithm on wikipedia
  const float x3 = p_pos.x;
  const float y3 = p_pos.y;

  const float x4 = p_pos.x + dirVec.x;
  const float y4 = p_pos.y + dirVec.y;

  //Loop through every wall in array
  for (int i = 0; i < walls.size(); i++) {

    //More variables
    const float x1 = walls[i].a.x;
    const float y1 = walls[i].a.y;

    const float x2 = walls[i].b.x;
    const float y2 = walls[i].b.y;

    const float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    //If this is 0, it means that the ray is completely parallel to the wall it is checking, and den is used as a divisor, so continue to not get any errors
    if (den == 0) {
      continue;
    }

    //More variables for line-line intersection algorithm on wikipedia
    const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    const float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

    //Check if the lines intersect
    if (t > 0 && t < 1 && u > 0) {
      //Set hit to true  
      p_hit = true;

      //Get point of where they intersect
      Vector point((x1 + t * (x2 - x1)), y1 + t * (y2 - y1));

      //If distance from the rays position to the point is less than the current record or the record has not been set yet
      if (dist(p_pos, point) < dist(p_pos, record) || (record.x == 0 && record.y == 0)) {
        //Set the record to this point  
        record = point;

        //And set wall hit index to the current index
        p_wallHitIndex = i;
      }
    }
  }

  //If after checking all the walls, a wall wasn't hit, return 0;
  if (!p_hit) {
    return 0;
  }

  //Else set the point of collision of this ray to the record vector
  m_pointOfCollision = record;

  //And return the distance between this rays position and the point of collision
  return dist(p_pos, m_pointOfCollision);
}
