#include "Player.hpp"

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