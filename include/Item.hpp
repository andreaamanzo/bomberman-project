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

  Item(Type itemType, int x, int y);

private:
  inline const static Nc::Sprite2x3 s_spriteType1{ L"nop", L"nop", Nc::Color::Yellow };
  inline const static Nc::Sprite2x3 s_spriteType2{ L"nop", L"nop", Nc::Color::Yellow };
  // ...
  
};

#endif