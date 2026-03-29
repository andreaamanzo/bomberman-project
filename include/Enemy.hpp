#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "NcWrapper.hpp"

class Enemy : public Entity 
{
public:
  Enemy() = default;
  Enemy(int x, int y);
  
  void move();

private:
  inline const static Nc::Sprite2x3 s_enemySprite{ "⋋▃⋌", "╱║╲", Nc::Color::Red };
};


#endif