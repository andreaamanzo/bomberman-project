#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "NcWrapper.hpp"

class Entity
{
public:
  Entity() = default;
  Entity(const Nc::Sprite2x3& sprite, int x = 0, int y = 0);

  void draw(Nc::Window& window) const;
  int getX() const;
  int getY() const;
  void setPos(int x, int y);
  bool collide(const Entity& other);

protected:
  Nc::Sprite2x3 m_sprite{ "   ", "   ", Nc::Color::Default };
  int m_x{};
  int m_y{};
};


#endif