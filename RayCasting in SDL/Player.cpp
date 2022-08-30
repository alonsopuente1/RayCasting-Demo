#include "Player.h"

Player::Player(float x, float y) : m_pos(x, y) {
  //Set direction facing down
  m_dir = INITDIR;

  //Set keyPressed booleans to false to not start moving or rotating as soon as the application starts
  p_wPressed = false;
  p_sPressed = false;
  p_aPressed = false;
  p_dPressed = false;
  p_laPressed = false;
  p_raPressed = false;

  //Add rays within the FOV angle, plus the players direction
  for (float i = -(FOV / 2); i <= FOV / 2; i += (float)FOV / RESOLUTION) {
    m_rays.push_back(Ray(m_pos, radians(i) + m_dir));
  }
}

void Player::Draw(SDL_Renderer* render) {
  //If there is nothing in the scene, return;
  if (m_scene.size() == 0)
    return;

  //Declare variables
  float rectHeight;
  float brightness;

  //Width of every rectangle drawn on the screen
  float rectWidth = (float)WIDTH / RESOLUTION;

  //For every variable in the m_scene array, draw the rectangle
  for (int i = 0; i < m_scene.size(); i++) {
    //If the ray didn't hit anything, skip drawing the rectangle
    if (!m_rays[i].p_hit)
      continue;

    //Set distance to current 
    float distance = m_scene[i];

    //Only fix the fish eye lens effect if false
    if (!FISHEYE) {
      //Angle of ray relative to the angle of the player, used for fish eye lens effect fix
      float newAng = m_dir - m_rays[i].p_dir;

      //If greater than 360 degrees, take away 360
      if (newAng < 0)
        newAng += PI * 2;
      //If less than 0, add 360, done in terms of radians
      else if (newAng > PI * 2)
        newAng -= PI * 2;

      //Fish eye lens effect fix
      distance *= cos(newAng);
    }

    //Map the brightness
    brightness = map(distance, 0, WIDTH, 150, 0);

    //Default shading to true
    bool shaded = true;

    //Make a wall object and set it to the wall that the current ray hit
    Wall wallHit = m_walls[m_rays[i].p_wallHitIndex];

    //Depending on the position of the ray to the wall, make shaded false. Shaded is false if the ray is above or to the right of a wall
    shaded = !((wallHit.a.y == wallHit.b.y && m_rays[i].p_pos.y < wallHit.a.y) || (wallHit.a.x == wallHit.b.x && m_rays[i].p_pos.x > wallHit.a.x));

    //If not shaded, make the rectangle brighter
    if (!shaded)
      brightness += 105;
    //Else make the rectangle darker
    else
      brightness -= 10;

    //Set rectangle height, the further away, the smaller therefore the closer, the bigger
    rectHeight = (HEIGHT * 50) / distance;

    //Cap the rectangle height to the height of the screen
    if (rectHeight > HEIGHT)
      rectHeight = HEIGHT;

    //Cap the brightness
    if (brightness > 255)
      brightness = 255;
    //Set it to at least 0
    else if (brightness < 0)
      brightness = 0;

    //Set colour to brightness
    SDL_SetRenderDrawColor(render, 0, 0, brightness, SDL_ALPHA_OPAQUE);

    //Draws rectangle on the screen
    rect(render, (i * rectWidth) + (rectWidth / 2), HEIGHT / 2, rectWidth, rectHeight);
  }

  //If the showmap variable is true
  if (SHOWMAP) {
    //Offset of the direction that the player is looking at
    Vector offset(cos(m_dir) * 10, sin(m_dir) * 10);

    //Draw Rectangle which represents the player
    SDL_FRect player = { m_pos.x - 2, m_pos.y - 2, 4, 4 };
    SDL_RenderDrawRectF(render, &player);

    //Draw line which represents the direction the player is looking at
    SDL_RenderDrawLineF(render, m_pos.x, m_pos.y, m_pos.x + offset.x, m_pos.y + offset.y);

    //Draw all the rays and all the walls
    for (Ray ray : m_rays)
      ray.Draw(render);
    for (Wall wall : m_walls)
      wall.Draw(render);
  }
}

void Player::Update(float mouseX) {
  bool updateScene = false;
  bool moved = false;
  float totalRotation = 0;
  float rotateSpeed = radians(ROTATESPEED);

  //Handle any rotation first


  if (mouseX != 0) {
    //Rotate the player
    Rotate(mouseX);

    totalRotation += mouseX;
  }

  //Rotate left if left arrow pressed
  if (p_laPressed) {
    //Rotate the player
    Rotate(-rotateSpeed);
  
    //Add to total rotation
    totalRotation += -rotateSpeed;
  }

  //Rotate right if right arrow pressed
  if (p_raPressed) {
    //Rotate the player
    Rotate(rotateSpeed);

    //Add to total rotation
    totalRotation += rotateSpeed;
  }


  //Then handle movement

  
  //Move forward and update m_scene if w is pressed
  if (p_wPressed) {
    //Move depending on MOVESPEED variable in "Utilities.h"
    Move(1);

    //Set moved to true to update rays position at the end of the function
    moved = true;
  }

  //Move backward and update m_scene if s is pressed
  if (p_sPressed) {
    //Move depending on the MOVESPEED variable but negative to move backwards
    Move(-1);

    //Set moved to true to update rays position at the end of the function
    moved = true;
  }
  
  //Strafe left and update m_scene if a is pressed
  if (p_aPressed) {
    //The direction to move in, -90 degrees / left
    Strafe(-PI / 2);

    //Set moved to true to update rays position at the end of the function
    moved = true;
  }

  //Strafe right and update m_scene if d is pressed
  if (p_dPressed) {
    //The direction to move in, 90 degrees / right
    Strafe(PI / 2);

    //Set moved to true to update rays position at the end of the function
    moved = true;
  }

  //If the player has moved at all, update the rays' position
  if (moved)
    UpdateRaysPos();

  //If the player has rotated at all, update the rays' rotation
  if (totalRotation != 0)
    RotateRays(totalRotation);

  //Finally, if the player has rotated at all OR the player has moved, update m_scene array
  if (totalRotation != 0 || moved) {
    m_scene.clear();
    for (int i = 0; i < m_rays.size(); i++)
    {
      m_scene.push_back(m_rays[i].Check(m_walls));
    }
  }
}

void Player::Rotate(float ang) {
  //Add angle passed through the function, in radians
  m_dir += ang;
}

void Player::Move(float dir) {
  //This creates a vector which stores the velocity of the player in the direction it is facing
  Vector offset(cos(m_dir), sin(m_dir));
  offset.Mult(MOVESPEED * dir);

  //This moves the player based on the velocity vector
  Collision(offset);
}

void Player::InitWalls(std::vector<Wall> walls) {
  //Set the private variable to whatever is passed through the function
  m_walls = walls;

  //Temporary wall array
  std::vector<Wall> tempWalls;

  //Start at index 5 to ignore outer walls
  for (int i = 5; i <= m_walls.size(); i++)
  {
    tempWalls.push_back(m_walls[i - 1]);
    //One rectangle has 4 four walls, for this reason every four walls, we store the x y width and height of a rectangle in the array
    if (i % 4 == 0) {
      SDL_FRect rect = { tempWalls[0].a.x, tempWalls[0].a.y, tempWalls[1].b.x - tempWalls[0].a.x, tempWalls[1].b.y - tempWalls[0].a.y };
      m_wallRect.push_back(rect);
      //Reset the tempWalls array once finished
      tempWalls.clear();
    }
  }
}

void Player::Strafe(float dir) {
  //Rotates the current direction
  float tempDir = m_dir + dir;

  //The offset of the position
  Vector velocity(cos(tempDir) * MOVESPEED, sin(tempDir) * MOVESPEED);

  //This moves the player based on the velocity
  Collision(velocity);
}

void Player::Collision(Vector offset) {
  //At first, the collision checks are false
  bool xCollision = false;
  bool yCollision = false;

  //Check collision with walls in the m_wallRect array
  for (int i = 0; i < m_wallRect.size(); i++) {
    SDL_FRect currentWall = m_wallRect[i];

    //Check if adding x offset puts player in wall
    Vector tempPos(m_pos.x + offset.x, m_pos.y);
    if (tempPos.x > currentWall.x && tempPos.x < currentWall.x + currentWall.w && tempPos.y > currentWall.y && tempPos.y < currentWall.y + currentWall.h) {
      xCollision = true;
    }

    //Check if adding y offset puts player in wall
    tempPos.Set(m_pos.x, m_pos.y + offset.y);
    if (tempPos.x > currentWall.x && tempPos.x < currentWall.x + currentWall.w && tempPos.y > currentWall.y && tempPos.y < currentWall.y + currentWall.h) {
      yCollision = true;
    }

    //If both x and y collision are true, return
    if (xCollision && yCollision)
      return;
  }

  //If xCollsion true and yCollision false, only move in the y axis
  if (xCollision && !yCollision)
    m_pos.Add(0, offset.y);

  //If xCollision false and yCollision true, only move in the x axis
  else if (!xCollision && yCollision)
    m_pos.Add(offset.x, 0);

  //If xCollision and yCollision false, move in both axis
  else if (!xCollision && !yCollision)
    m_pos.Add(offset);

  //Check outer walls
  if (m_pos.x <= 1)
    m_pos.x = 2;
  else if (m_pos.x >= WIDTH - 1)
    m_pos.x = WIDTH - 2;
  else if (m_pos.y <= 1)
    m_pos.y = 2;
  else if (m_pos.y >= HEIGHT - 1)
    m_pos.y = HEIGHT - 2;
}

void Player::RotateRays(float ang) {
  for (int i = 0; i < m_rays.size(); i++)
  {
    m_rays[i].Rotate(ang);
  }
}

void Player::UpdateRaysPos() {
  //Loop through all rays
  for (int i = 0; i < m_rays.size(); i++) {
    //Update the rays with the player's position
    m_rays[i].Update(m_pos);
  }
}
