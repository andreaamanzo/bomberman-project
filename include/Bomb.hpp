#ifndef BOMB_HPP
#define BOMB_HPP

#include "Entity.hpp"

class Bomb : public Entity
{
public:
  Bomb(int x, int y, int radius);

private:
  inline const static Nc::Sprite2x3 s_bombSprite{ " ╽ ", "(●)", Nc::Color::Yellow };

  int m_radius{};
  
};

#endif