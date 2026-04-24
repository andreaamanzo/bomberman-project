#include "Item.hpp"

Item::Item()
  : Entity{ s_spriteTypeNull }
{ }

Item::Item(Type itemType, int x, int y)
  : Entity{ getSprite(itemType), x, y }
{ 
  m_type = itemType;
}

const Nc::Sprite2x3& Item::getSprite(Type type)
{
  switch (type)
  {
  case Type::Null:
    return s_spriteTypeNull;
  case Type::IncrementBombRadius:
    return s_spriteTypeIncrementBombRadius;
  case Type::IncrementMaxBombs:
    return s_spriteTypeIncrementMaxBombs;
  case Type::OneUp:
    return s_spriteTypeOneUp;
  case Type::Invulnerability:
    return s_spriteTypeInvulnerability;
  case Type::Ice:
    return s_spriteTypeIce;
  }

  return s_spriteTypeNull;
}

Item::Type Item::getType() const
{
  return m_type;
}

bool Item::isTimed() const
{
  return (m_type == Type::Invulnerability || m_type == Type::Ice);
}

void Item::setPowerDuration(int secDuration)
{
  m_powerDuration = std::chrono::seconds{ secDuration };
}

void Item::activate()
{
  m_expiration = Clock::now() + m_powerDuration;
}

bool Item::isActive()
{
  if (!isTimed()) return true;

  // ** tipo esplicito: std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
  auto start = std::chrono::steady_clock::now();

  return (start <= m_expiration);
}