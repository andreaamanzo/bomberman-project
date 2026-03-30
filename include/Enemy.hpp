#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "NcWrapper.hpp"
#include "Direction.hpp"

class Enemy : public Entity 
{
public:
  //TODO: copiare enum da item
  Enemy() = default;
  Enemy(int x, int y);

  void setDirection(Direction newDirection); // ! ALEGODA !! cosa metti le funzioni nel .hpp you fucking retarded
  void move();

private:
  inline const static Nc::Sprite2x3 s_enemySprite{ "°|°", "/ \\ ", Nc::Color::Red };

  Direction m_direction{ Direction::Left };

};

#endif