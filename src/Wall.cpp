#include "Wall.hpp"

Wall::Wall(int x, int y, bool isBreakable)
  : Entity{ isBreakable ? s_breakableSprite : s_unbreakableSprite, x, y }
  , m_isBreakable{ isBreakable }
{ }

bool Wall::isBreakable() const
{
  return m_isBreakable;
}