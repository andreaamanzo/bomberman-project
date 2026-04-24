#include "Enemy.hpp"
#include "Bomb.hpp"
#include "Direction.hpp"
#include "Movable.hpp"
#include "NcWrapper.hpp"
#include <chrono>

Enemy::Enemy(Type enemyType, int x, int y)
  : Movable{getSprite(enemyType), x, y, getSpeed(enemyType)},
    m_type{enemyType}, m_points{getPoints(enemyType)} {}

void Enemy::move() { Movable::move(m_direction, 1); }

void Enemy::setDirection(Direction newDirection) { m_direction = newDirection; }

Enemy::Type Enemy::getType() const { return m_type; }

int Enemy::getPoints() const { return m_points; }

Direction Enemy::getDirection() const { return m_direction; }

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

int Enemy::getPoints(Type enemyType) {
  if (enemyType == Type::First_Enemy)
    return 100;
  else if (enemyType == Type::Second_Enemy)
    return 250;
  else if (enemyType == Type::Third_Enemy)
    return 300;

  return 0;
}

int Enemy::getSpeed(Type enemyType) {
  if (enemyType == Type::First_Enemy)
    return 70;
  else if (enemyType == Type::Second_Enemy)
    return 30;
  else if (enemyType == Type::Third_Enemy)
    return 60;
  return 0;
}

bool Enemy::isTimerActive() const { return m_isTimerActive; }

void Enemy::setBombTimer(bool active) { m_isTimerActive = active; }

bool Enemy::checkIfShouldBomb() {
  using EnemyClock = std::chrono::steady_clock;

  if (!isTimerActive()) {
    m_nextBombCooldown = EnemyClock::now() + std::chrono::seconds(4);
    setBombTimer(true);
    return false;
  }

  if (isTimerActive() && EnemyClock::now() >= m_nextBombCooldown) {
    setBombTimer(false);
    return true;
  }
  return false;
}
void Enemy::surprise(bool set){
  if (set == true) m_surprise = true;
  else m_surprise = false;
}

bool Enemy::getSurpriseStatus(){
  return m_surprise;
}