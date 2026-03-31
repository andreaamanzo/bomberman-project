#include "Enemy.hpp"
#include "Bomb.hpp"
#include "Entity.hpp"
#include "Level.hpp"
#include "Sprite2x3.hpp"

Enemy::Enemy(Type enemyType, int x, int y )
  : Entity{ getSprite(enemyType), x, y }, m_type{ enemyType }
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

const Nc::Sprite2x3& Enemy::getSprite(Type enemyType)
{
  switch (enemyType)
  {
  case Type::Null:
    return s_spriteTypeNull;
  case Type::First_Enemy:
    return s_enemy1;
  case Type:: Second_Enemy:
    return s_enemy2;
  }

  return s_spriteTypeNull;
}
