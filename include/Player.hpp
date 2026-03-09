#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "NcWrapper.hpp"
#include "Direction.hpp"
#include "Item.hpp"
#include "Bomb.hpp"

class Player : public Entity
{
public:
  Player();

  void move(Direction dir);
  Bomb placeBomb();
  void restoreBomb();

private:
  inline const static Nc::Sprite2x3 s_sprite{ L"ʘ‿ʘ", L"╰╩╯", Nc::Color::Green };

  int m_lives{};
  int m_bombRadius{ 1 };
  int m_maxBombs{ 1 };
  int m_placedBombs{ 0 };

  Item items[];

};

#endif