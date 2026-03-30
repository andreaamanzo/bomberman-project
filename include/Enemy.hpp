#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "NcWrapper.hpp"
#include "Direction.hpp"

class Enemy : public Entity 
{
public:
Enemy() = default;
Enemy(const Nc::Sprite2x3& sprite, int x, int y);

void setDirection(int newDirection) {
  m_direction = newDirection;
}
void move();
inline const static Nc::Sprite2x3 s_enemySprite{ "°|°", "/ \\ ", Nc::Color::Red };

private:
  int m_direction{0}; //0 lx, 1 up, 2 rx, 3 dw

};



#endif