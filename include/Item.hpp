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
    IncrementMaxBombs,
    Invulnerability,
    OneUp,
    TimedIncrementBombPower,
  };

  Item();
  Item(Type itemType, int x, int y);

  Item::Type getType() const;
  
  void setPowerDuration(int secDuration);
  void activate();
  bool isTimed() const;
  bool isActive();
  void removeItem();

private:
  inline const static Nc::Sprite2x3 s_spriteTypeNull{ "   ", "   ", Nc::Color::Default };
  inline const static Nc::Sprite2x3 s_spriteTypeIncrementMaxBombs{ "|+|", "|+|", Nc::Color::Yellow };
  inline const static Nc::Sprite2x3 s_spriteTypeIncrementBombRadius{ "|↑|", "|↓|", Nc::Color::Yellow };
  inline const static Nc::Sprite2x3 s_spriteTypeOneUp{ "|❤|", "|❤|", Nc::Color::Yellow };
  inline const static Nc::Sprite2x3 s_spriteTypeInvulnerability{ "|⛨|", "|⛨|", Nc::Color::Yellow };
  inline const static Nc::Sprite2x3 s_spriteTypeTimedIncrementBombPower{ "|☀|", "|☀|", Nc::Color::Yellow };


  using Clock = std::chrono::steady_clock;
  Clock::time_point m_expiration{ };
  std::chrono::seconds m_powerDuration{ 10 };

  Type m_type{ Type::Null };

  static const Nc::Sprite2x3& getSprite(Type type);
};

#endif