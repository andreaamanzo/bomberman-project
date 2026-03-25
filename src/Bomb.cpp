#include "Bomb.hpp"
#include <chrono>

Bomb::Bomb()
  : Entity{ s_bombSprite }
{ }

Bomb::Bomb(int x, int y, int radius)
  : Entity{ s_bombSprite, x, y }
  , m_radius{ radius }
  , m_status{ Status::Placed }
  , m_startTime{ Clock::now() }
  , m_lastColorSwitch{ Clock::now() }
{ }

void Bomb::update()
{
  Clock::time_point now = Clock::now();

  if (now - m_lastColorSwitch > s_switchColorTime)
  {
    m_useFirstColor = !m_useFirstColor;
    m_lastColorSwitch = now;

    if (m_useFirstColor)
      m_sprite.setColor(s_color1);
    else
      m_sprite.setColor(s_color2);
  }

  switch (m_status)
  {
  case Status::Placed:
    if (now - m_startTime > s_placementTime) 
    {
      m_status = Status::Exploding;
      m_startTime = now; // reset timer
    }
    break;

  case Status::Exploding:
    if (now - m_startTime > s_explosionTime) 
    {
      m_status = Status::Finished;
    }
    break;

  case Status::Finished:
    break;
  }
}

Bomb::Status Bomb::getStatus()
{
  update();

  return m_status;
}

int Bomb::getRadius() const
{
  return m_radius;
}

