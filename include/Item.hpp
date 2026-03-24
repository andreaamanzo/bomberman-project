#ifndef ITEM_HPP
#define ITEM_HPP

#include "Entity.hpp"
#include "NcWrapper.hpp"

class Item : public Entity
{
public:
  enum class Type
  {
    Null,
    IncrementBombRadius,
    IncrementSpeed,
    IncrementMaxBombs,
  };

  Item();
  Item(Type itemType, int x, int y);

private:
  inline const static Nc::Sprite2x3 s_spriteTypeNull{ "   ", "   ", Nc::Color::Default };
  inline const static Nc::Sprite2x3 s_spriteTypeIncrementBombRadius{ "nop", "nop", Nc::Color::Yellow };
  inline const static Nc::Sprite2x3 s_spriteTypeIncrementSpeed{ "nop", "nop", Nc::Color::Yellow };
  inline const static Nc::Sprite2x3 s_spriteTypeIncrementMaxBombs{ "nop", "nop", Nc::Color::Yellow };

  Type m_type{ Type::Null };

  static const Nc::Sprite2x3& getSprite(Type type);
};

#endif