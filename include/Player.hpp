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
  Player(int lives, int x, int y);

  void move(Direction dir);
  Bomb* placeBomb();
  void restoreBomb();
  void decreaseLife();
  void collectItem(const Item& item);

private:
  inline const static Nc::Sprite2x3 s_playerSprite{ "ʘ‿ʘ", "╰╩╯", Nc::Color::Green };

  int m_lives{};
  int m_bombRadius{ 1 };
  int m_maxBombs{ 1 };
  int m_placedBombs{ 0 };

  // List<Item> m_items

};

#endif