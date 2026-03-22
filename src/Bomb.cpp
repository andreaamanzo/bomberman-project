#include "Bomb.hpp"

Bomb::Bomb(int x, int y, int radius)
  : Entity{ s_bombSprite, x, y }
  , m_radius{ radius }
{ }

