#include "Enemy.hpp"
#include "Movable.hpp"
#include "NcWrapper.hpp"
#include "Direction.hpp"

// PER ALE: ho harcodato la "velocità" a 50, puoi fare una funzione che a seconda del nemico imposta una certa velocità
Enemy::Enemy(Type enemyType, int x, int y )
  : Movable{ getSprite(enemyType), x, y, 60 } 
  , m_type{ enemyType }
  , m_points{getPoints(enemyType)}
{}

void Enemy::move() 
{
  Movable::move(m_direction, 1);
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

int Enemy::getPoints(Type enemyType) {
  if (enemyType == Type::First_Enemy) return 100;
  else if (enemyType == Type::Second_Enemy) return 250;
  return 0;
}

int Enemy::getEnemyPoints(){
  return m_points;
}

