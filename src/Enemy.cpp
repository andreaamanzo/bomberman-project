#include "Enemy.hpp"
#include "Bomb.hpp"
#include "Entity.hpp"
#include "Level.hpp"
#include "Sprite2x3.hpp"

Enemy::Enemy(int x, int y )
: Entity{s_enemySprite, x, y}
{}

void Enemy::move() 
{
  switch (m_direction)
  {
  case Direction::Up:
    m_y -= 1;
    break;
  case Direction::Down:
    m_y += 1;
    break;
  case Direction::Right:
    m_x += 1;
    break;
  case Direction::Left:
    m_x -= 1;
    break;
  default:
    break;
  }    
}

void Enemy::setDirection(Direction newDirection) 
{
  m_direction = newDirection;
}
