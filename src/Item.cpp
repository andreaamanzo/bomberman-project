#include "Item.hpp"

Item::Item()
  : Entity{ s_spriteTypeNull }
{ }

Item::Item(Type itemType, int x, int y)
  : Entity{ getSprite(itemType), x, y }
  , m_type{ itemType }
{ }

const Nc::Sprite2x3& Item::getSprite(Type type)
{
  switch (type)
  {
  case Type::Null:
    return s_spriteTypeNull;
  case Type::IncrementBombRadius:
    return s_spriteTypeIncrementBombRadius;
  case Type::IncrementSpeed:
    return s_spriteTypeIncrementSpeed;
  case Type::IncrementMaxBombs:
    return s_spriteTypeIncrementMaxBombs;
  }

  return s_spriteTypeNull;
}

Item::Type Item::getType() const
{
  return m_type;
}

bool Item::isTimed() const
{
  return (m_type == Type::Invulnerability || m_type == Type::TimedIncrementBombRadius);
}

void Item::activate()
{
  auto m_expiration = std::chrono::steady_clock::now() + m_powerDuration;
}

/*
bool Item::isActive()
{
  // ** tipo esplicito: std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
  auto start = std::chrono::steady_clock::now();
  auto expiration = start + m_powerDuration;

  return (start <= end);
}
*/