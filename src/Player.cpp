#include "Player.hpp"
#include "Bomb.hpp"

Player::Player(int lives, int x, int y)
  : Entity{ s_playerSprite, x, y }
  , m_lives{ lives }
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