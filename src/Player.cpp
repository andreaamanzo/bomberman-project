#include "Player.hpp"
#include "Bomb.hpp"

Player::Player(int lives, int x, int y)
  : Movable{ s_playerSprite, x, y, 0 }
  , m_lives{ lives }
  , m_respownPoint{ x, y }
{ }

void Player::move(Direction dir)
{
  Movable::move(dir, m_velocity);
}

Bomb Player::placeBomb()
{
  if (m_placedBombs >= m_maxBombs) return Bomb{};

  m_placedBombs++;
  
  return Bomb{ m_x, m_y, m_bombRadius };
}

void Player::restoreBomb()
{
  if (m_placedBombs > 0)
    m_placedBombs--;
}

void Player::setRespownPoint(int x, int y)
{
  m_respownPoint = { x, y };
}

void Player::onHit()
{
  if (!m_isInvincible)
  {
    m_lives--;
    setPos(m_respownPoint.x, m_respownPoint.y);
  }
}

bool Player::isAlive() const 
{
  return m_lives > 0;
}

void Player::collectItem(const Item& item)
{
  switch (item.getType())
  {
  case Item::Type::Null :
    break;
  
  case Item::Type::IncrementBombRadius :
    m_bombRadius++;
    break;

  case Item::Type::IncrementMaxBombs :
    m_maxBombs++;
    break;

  case Item::Type::Invulnerability :
    // TODO
    break;

  case Item::Type::TimedIncrementBombRadius :
    // TODO
    break;

  case Item::Type::IncrementSpeed :
    // TODO: quando viene gestita la velocità
    break;
  }
}

void Player::addPoints(int points) 
{
  m_points =  points;
}

int Player::getPoints() const
{
  return m_points;
}

int Player::getLives() const
{
  return m_lives;
}
