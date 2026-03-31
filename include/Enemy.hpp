#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Direction.hpp"
#include "Entity.hpp"
#include "NcWrapper.hpp"

class Enemy : public Entity {
public:
  enum class Type{
    Null,
    First_Enemy,
    Second_Enemy,
  };
  Enemy() = default;
  Enemy(Type enemyType, int x, int y);

  void setDirection(Direction newDirection);
  void move();
  static const Nc::Sprite2x3& getSprite(Type enemyType);


private:
  Type m_type{Type::Null};
  inline const static Nc::Sprite2x3 s_spriteTypeNull{ "   ", "   ", Nc::Color::Default };
  inline const static Nc::Sprite2x3 s_enemy1{"°|°", "/ \\ ", Nc::Color::Red};
  inline const static Nc::Sprite2x3 s_enemy2{"ò_ó", "###", Nc::Color::Red};
  Direction m_direction{Direction::Left};
};

#endif