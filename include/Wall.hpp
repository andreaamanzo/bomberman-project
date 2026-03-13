#ifndef WALL_HPP
#define WALL_HPP

#include "NcWrapper.hpp"
#include "Entity.hpp"

class Wall : public Entity
{
public:
  Wall(int x, int y, bool isBreakable);

  bool isBreakable() const;

private:
  inline const static Nc::Sprite2x3 s_breakableSprite{ "▚▞▚", "▚▞▚", Nc::Color::White };
  inline const static Nc::Sprite2x3 s_unbreakableSprite{ "███", "███", Nc::Color::White };
  
  bool m_isBreakable{};
};

#endif