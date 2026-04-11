#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Direction.hpp"
#include "Movable.hpp"
#include "NcWrapper.hpp"

class LevelList;

class Enemy : public Movable 
{
public:
  LevelList* currentLevel;
  enum class Type
  {
    Null,
    First_Enemy,
    Second_Enemy,
    Third_Enemy,
  };
  Enemy() = default;
  Enemy(Type enemyType, int x, int y);

  void setDirection(Direction newDirection);
  void move();
  Direction getDirection() const { return m_direction; }
  int getEnemySpeed();
  int getEnemyPoints();
  void specialAbility(Type enemyType);
  
  
  private:
  Type m_type{Type::Null};
  static const Nc::Sprite2x3& getSprite(Type enemyType);
  inline const static Nc::Sprite2x3 s_spriteTypeNull{ "   ", "   ", Nc::Color::Default };
  inline const static Nc::Sprite2x3 s_enemy1{"°|°", "/ \\ ", Nc::Color::Red};
  inline const static Nc::Sprite2x3 s_enemy2{"ò_ó", "###", Nc::Color::Red};
  inline const static Nc::Sprite2x3 s_enemy3{"⋋▃⋌", "╱║╲", Nc::Color::Red};
  Direction m_direction{Direction::Left};
  int setPoints(Type enemyType);
  int m_points;
  int setSpeed(Type enemyType);
  std::chrono::steady_clock::time_point lastActionTime;
  std::chrono::milliseconds actionInterval{3000};
};

#endif