#ifndef ITEM_HPP
#define ITEM_HPP

#include "Entity.hpp"
#include "NcWrapper.hpp"

#include <chrono>

class Item : public Entity
{
public:
  enum class Type
  {
    Null,
    IncrementBombRadius,
    IncrementSpeed,
    IncrementMaxBombs,
    Invulnerability,
    TimedIncrementBombRadius,
  };

  Item();
  Item(Type itemType, int x, int y);

  Item::Type getType() const;

  bool isTimed() const;

  // TODO: metodi per gestitre items a tempo
  void activate();
  bool isActive();

private:
  inline const static Nc::Sprite2x3 s_spriteTypeNull{ "   ", "   ", Nc::Color::Default };
  inline const static Nc::Sprite2x3 s_spriteTypeIncrementBombRadius{ "nop", "nop", Nc::Color::Yellow };
  inline const static Nc::Sprite2x3 s_spriteTypeIncrementSpeed{ "nop", "nop", Nc::Color::Yellow };
  inline const static Nc::Sprite2x3 s_spriteTypeIncrementMaxBombs{ "nop", "nop", Nc::Color::Yellow };

  // ! UNDER CONSTRUCTION !
  using Clock = std::chrono::steady_clock;
  const std::chrono::seconds m_powerDuration{ 10 };
  Clock::time_point m_expiration;
  // ! UNDER CONSTRUCTION !

  Type m_type{ Type::Null };

  static const Nc::Sprite2x3& getSprite(Type type);
};

#endif