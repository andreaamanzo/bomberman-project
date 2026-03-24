#ifndef BOMB_HPP
#define BOMB_HPP

#include "Entity.hpp"

class Bomb : public Entity
{
public:
  Bomb();
  Bomb(int x, int y, int radius);

private:
  inline const static Nc::Sprite2x3 s_bombSprite{ " ╽ ", "(●)", Nc::Color::Orange };

  int m_radius{};
  
};

#endif