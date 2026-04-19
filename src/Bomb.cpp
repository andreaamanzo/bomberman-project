#include "Bomb.hpp"
#include <chrono>

Bomb::Bomb()
  : Entity{ s_bombSprite }
{ }

Bomb::Bomb(int x, int y, int radius, bool isEnemy)
  : Entity{ isEnemy ? s_enemyBombSprite : s_bombSprite, x, y } // '?' se true valuta la prima se no la seconda
  , m_radius{ radius }
  , m_status{ Status::Placed }
  , m_startTime{ Clock::now() }
  , m_lastColorSwitch{ Clock::now() }
  , m_isEnemy{ isEnemy }
{ }

void Bomb::update()
{
  Clock::time_point now = Clock::now();

  if (now - m_lastColorSwitch > s_switchColorTime)
  {
    m_useFirstColor = !m_useFirstColor;
    m_lastColorSwitch = now;

if (m_isEnemy)
{
  if (m_useFirstColor)
    m_sprite.setColor(s_ecolor1);
  else
    m_sprite.setColor(s_ecolor2);
}
else
{
  if (m_useFirstColor)
    m_sprite.setColor(s_color1);
  else
    m_sprite.setColor(s_color2);
}
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

bool Bomb::hasExploded() const
{
  return m_hasExploded;
}

void Bomb::setExploded(bool set)
{
  m_hasExploded = set;
}

const Nc::Point* Bomb::getExplosionCells() const
{
  return m_explosionCells;
}

int Bomb::getExplosionCount() const
{
  return m_explosionCount;
}

void Bomb::setExplosionCells(const Nc::Point cells[], int count)
{
  if (count > s_maxExplosionCells)
    count = s_maxExplosionCells; // sicurezza

  m_explosionCount = count;

  for (int i = 0; i < count; i++)
    m_explosionCells[i] = cells[i];
}

bool Bomb::isEnemy() const {
  return m_isEnemy;
}