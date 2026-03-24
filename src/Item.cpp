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