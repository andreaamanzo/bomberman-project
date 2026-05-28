#include "Movable.hpp"
#include "Entity.hpp"
#include <chrono>

Movable::Movable(const Nc::Sprite2x3& sprite, int x, int y, int delaySpeedMillisecods)
  : Entity{ sprite, x, y }
  , m_delaySpeed{ Milliseconds{ delaySpeedMillisecods } }
{ }

void Movable::move(Direction dir)
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

  m_lastMoveTime = Clock::now();
}

void Movable::setDelaySpeed(int milliseconds)
{
  m_delaySpeed = Milliseconds{ milliseconds };
}

bool Movable::shouldMove() const
{
  Clock::time_point now = Clock::now();

  return now - m_lastMoveTime >= m_delaySpeed;
}
