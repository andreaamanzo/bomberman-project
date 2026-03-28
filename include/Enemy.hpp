#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "NcWrapper.hpp"

class Enemy : public Entity 
{
public:
  Enemy() = default;
  Enemy(const Nc::Sprite2x3& sprite, int x, int y);
  
  void move();

private:

};

//possible enemy sprite : inline const static Nc::Sprite2x3 e_sprite{ L"°|°", L"/ \\ ", Nc::Color::Red };


#endif