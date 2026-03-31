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
  Bomb placeBomb();
  void restoreBomb();
  // gestisce la perdita della vita e fa respownare il player nella poszione giusta
  void onHit();
  void collectItem(const Item& item);
  void setRespownPoint(int x, int y);
  bool isAlive() const;

private:
  inline const static Nc::Sprite2x3 s_playerSprite{ "ʘ‿ʘ", "╰╩╯", Nc::Color::Green };

  inline constexpr static int s_maxLengthArrays{ 64 };

  int m_lives{ 1 };
  int m_bombRadius{ 2 };
  int m_maxBombs{ 1 };
  int m_placedBombs{ 0 };
  Nc::Point m_respownPoint{ 0, 0 };
  Item  m_items[s_maxLengthArrays]{};
  int   m_itemsSize{ 0 };

};

#endif