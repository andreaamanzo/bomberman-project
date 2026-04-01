#include "Movable.hpp"
#include "Entity.hpp"

Movable::Movable(const Nc::Sprite2x3& sprite, int x, int y, int delaySpeedMillisecods)
  : Entity{ sprite, x, y }
  , m_delaySpeed{ Milliseconds{ delaySpeedMillisecods } }
{ }

void Movable::move(Direction dir, int velocity)
{
  switch (dir)
  {
  case Direction::Up:
    m_y -= velocity;
    break;
  case Direction::Down:
    m_y += velocity;
    break;
  case Direction::Right:
    m_x += velocity;
    break;
  case Direction::Left:
    m_x -= velocity;
    break;
  default:
    break;
  }

  m_lastMoveTime = Clock::now();
}

void Movable::setDelaySpeed(int milliseconds)
{
  m_delaySpeed = Milliseconds{ milliseconds };
}

bool Movable::shouldMove()
{
  Clock::time_point now = Clock::now();

  return now - m_lastMoveTime >= m_delaySpeed;
}

