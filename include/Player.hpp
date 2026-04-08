#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Movable.hpp"
#include "NcWrapper.hpp"
#include "Direction.hpp"
#include "Item.hpp"
#include "Bomb.hpp"

class Player : public Movable
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
  int getLives() const;
  void handleItems();
  const Item* getItemsList() const;
  int getItemsListSize() const;
  void addPoints(int points);
  int getPoints() const;

private:
  inline const static Nc::Sprite2x3 s_playerSprite{ "ʘ‿ʘ", "╰╩╯", Nc::Color::Green };

  inline constexpr static int s_maxLengthArrays{ 64 };

  Nc::Point m_respawnPoint{ 0, 0 };
  int m_lives{ 1 };
  int m_bombRadius{ 2 };
  int m_maxBombs{ 1 };
  int m_placedBombs{ 0 };
  int m_velocity{ 1 };
  int m_itemsSize{ 0 };
  int m_points{ 0 };
  Item m_items[s_maxLengthArrays]{ };
  bool m_isInvincible{ false };

};

#endif