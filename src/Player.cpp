#include "Player.hpp"
#include "Bomb.hpp"

Player::Player(int lives, int x, int y)
  : Entity{ s_playerSprite, x, y }
  , m_lives{ lives }
  , m_respownPoint{ x, y }
{ }

void Player::move(Direction dir)
{
  switch (dir)
  {
  case Direction::Up:
    m_y -= 1;
    break;
  case Direction::Down:
    m_y += 1;
    break;
  case Direction::Right:
    m_x += 1;
    break;
  case Direction::Left:
    m_x -= 1;
    break;
  default:
    break;
  }
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
  m_lives--;
  setPos(m_respownPoint.x, m_respownPoint.y);
}

bool Player::isAlive() const 
{
  return m_lives > 0;
}