#include "Entity.hpp"
#include "NcWrapper.hpp"

Entity::Entity(const Nc::Sprite2x3& sprite, int x, int y)
  : m_sprite{ sprite }
  , m_x{ x }
  , m_y{ y }
{ }

void Entity::draw(Nc::Window& window) const
{
  window.draw(m_sprite, m_x, m_y);
}

int Entity::getX() const { return m_x; }

int Entity::getY() const { return m_y; }

void Entity::setPos(int x, int y)
{
  m_x = x;
  m_y = y;
}