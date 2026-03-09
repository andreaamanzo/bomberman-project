#ifndef BOMB_HPP
#define BOMB_HPP

#include "Entity.hpp"

class Bomb : public Entity
{
public:
  Bomb(int x, int y, int radius);

private:
  int m_radius{};
  
};

#endif