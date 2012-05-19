
#ifndef SPRITE_H
#define SPRITE_H 

#include <vector>

#include "Texture.h"
#include "Vector2D.h"

/**
 *   Sprites info for the game
 *      Normally this would have velocity, position and all that...
 *       However the Box2D lib is taking care of this for us so it is not 
 *       needed yet.
 */

class Sprite
{

  public:

  /// Graphics texture context info
  Texture texture;

  /// Size of the sprite (width.x, height.y)
  Vector2Df size;

  /// List of verticies
  std::vector<Vector2Df> vertex;

  std::vector<Vector2Df> texture_coords;

  Sprite():
    texture(),
    size()
  {
  }

};

#endif /* SPRITE_H */
