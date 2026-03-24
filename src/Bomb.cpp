#include "Bomb.hpp"

Bomb::Bomb()
  : Entity{ s_bombSprite }
{ }

Bomb::Bomb(int x, int y, int radius)
  : Entity{ s_bombSprite, x, y }
  , m_radius{ radius }
{ }

