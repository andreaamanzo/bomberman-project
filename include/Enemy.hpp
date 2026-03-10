#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "NcWrapper.hpp"

class Enemy : public Entity 
{
public:
  Enemy();
  
  void Kill_Enemy();
  void move();

private:

  bool alive;


};

//possible enemy sprite : inline const static Nc::Sprite2x3 e_sprite{ L"°|°", L"/ \\ ", Nc::Color::Red };


#endif