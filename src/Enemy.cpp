#include "Enemy.hpp"
#include "Direction.hpp"
#include "LevelList.hpp"
#include "Movable.hpp"
#include "NcWrapper.hpp"
#include <chrono>


Enemy::Enemy(Type enemyType, int x, int y)
    : Movable{getSprite(enemyType), x, y, setSpeed(enemyType)},
      m_type{enemyType}, m_points{setPoints(enemyType)} {}

void Enemy::move() { Movable::move(m_direction, 1); }

void Enemy::setDirection(Direction newDirection) { m_direction = newDirection; }

const Nc::Sprite2x3 &Enemy::getSprite(Type enemyType) {
  switch (enemyType) {
  case Type::Null:
    return s_spriteTypeNull;
  case Type::First_Enemy:
    return s_enemy1;
  case Type::Second_Enemy:
    return s_enemy2;
  case Type::Third_Enemy:
    return s_enemy3;
  }

  return s_spriteTypeNull;
}

int Enemy::setPoints(Type enemyType) {
  if (enemyType == Type::First_Enemy)
    return 100;
  else if (enemyType == Type::Second_Enemy)
    return 250;
  return 0;
}

int Enemy::getEnemyPoints() { return m_points; }

int Enemy::setSpeed(Type enemyType) {
  if (enemyType == Type::First_Enemy)
    return 40;
  else if (enemyType == Type::Second_Enemy)
    return 70;
  else if (enemyType == Type::Third_Enemy)
    return 60;
  return 0;
}

Enemy::Type Enemy::getType() const{
  return m_type;
}
