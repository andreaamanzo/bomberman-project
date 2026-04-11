#include "Enemy.hpp"
#include "Direction.hpp"
#include "LevelList.hpp"
#include "Movable.hpp"
#include "NcWrapper.hpp"
#include <chrono>

// PER ALE: ho harcodato la "velocità" a 50, puoi fare una funzione che a
// seconda del nemico imposta una certa velocità
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

/*int Enemy::getEnemySpeed(){
  auto duration = getSpeed();
  int ms_as_int = static_cast<int>(duration.count());
  return ms_as_int;
}*/

/*void Enemy::specialAbility(Type enemyType) {
  if (enemyType == Type::Third_Enemy) {
    int x = this->getX();
    int y = this->getY();
    int targetX = x - 1; // la bomba la mettiamo sempre dov'è il nemico e creiamo una sottoclasse bomba
    //che non da collisioni con nemico.
    }
  }
}*/
