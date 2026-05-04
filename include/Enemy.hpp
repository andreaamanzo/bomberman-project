#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Direction.hpp"
#include "Movable.hpp"
#include "NcWrapper.hpp"

class Enemy : public Movable 
{
public:
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
  Direction getDirection() const;
  int getPoints() const;
  Type getType() const;
  bool isTimerActive() const;
  void setBombTimer(bool active);
  bool checkIfShouldBomb();
  void surprise(bool set);
  bool getSurpriseStatus();

  private:
  inline const static Nc::Sprite2x3 s_spriteTypeNull{ "   ", "   ", Nc::Color::Default };
  inline const static Nc::Sprite2x3 s_enemy1{"°|°", "/ \\ ", Nc::Color::Red};
  inline const static Nc::Sprite2x3 s_enemy2{"ò_ó", "###", Nc::Color::Red};
  inline const static Nc::Sprite2x3 s_enemy3{"⋋▃⋌", "╱║╲", Nc::Color::Red};
  
  Type m_type{ Type::Null };
  Direction m_direction{ Direction::Left };
  int m_points;
  std::chrono::steady_clock::time_point m_lastActionTime;
  std::chrono::milliseconds m_actionInterval{ 3000 };
  std::chrono::steady_clock::time_point m_nextBombCooldown;
  bool m_isTimerActive;
  bool m_surprise{ false };

  static const Nc::Sprite2x3& getSprite(Type enemyType);
  static int getPoints(Type enemyType);
  static int getSpeed(Type enemyType);
};

#endif