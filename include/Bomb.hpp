#ifndef BOMB_HPP
#define BOMB_HPP

#include "Entity.hpp"
#include "NcWrapper.hpp"
#include "Settings.hpp"
#include <chrono>

class Bomb : public Entity
{
public:
  enum class Status
  {
    Placed,
    Exploding,
    Finished
  };

  enum class Type
  {
    Player,
    Enemy
  };

  Bomb();
  Bomb(int x, int y, int radius = 1, Type type = Type::Player);

  Status getStatus();
  Type getType() const;
  int getRadius() const;
  bool hasExploded() const;
  void setExploded(bool set);
  const Nc::Point* getExplosionCells() const;
  int getExplosionCount() const;
  void setExplosionCells(const Nc::Point cells[], int count);
  const Nc::Sprite2x3& getExplosionSprite() const;
  
  inline constexpr static int s_maxExplosionCells{ Settings::mapCols + Settings::mapRows };

protected:
  using Clock = std::chrono::steady_clock;
  
  inline const static Nc::Color s_color1{ Nc::Color::Orange };
  inline const static Nc::Color s_color2{ Nc::Color::Green };
  inline const static Nc::Color s_enemyColor1{ Nc::Color::Pink };
  inline const static Nc::Color s_enemyColor2{ Nc::Color::Red };
  inline const static Nc::Sprite2x3 s_enemyBombSprite{ " ◉ ", "[#]", s_enemyColor1 };
  inline const static Nc::Sprite2x3 s_bombSprite{ " ╽ ", "(●)", s_color1 };
  inline const static Nc::Sprite2x3 s_explosionSprite{ "███", "███", Nc::Color::Fire };
  inline const static Nc::Sprite2x3 s_enemyExplosionSprite{ "▜█▙", "▜█▙", Nc::Color::Red };
  inline const static std::chrono::milliseconds s_placementTime{ 3000 };    // 3 secondi
  inline const static std::chrono::milliseconds s_explosionTime{ 500 };     // 0.5 secondi
  inline const static std::chrono::milliseconds s_switchColorTime{ 400 };   // 0.4 secondi

  int m_radius{ 0 };
  Type m_type{ Type::Player };
  Status m_status{ Status::Finished };
  Clock::time_point m_startTime{};
  Clock::time_point m_lastColorSwitch{};
  bool m_useFirstColor{ true };
  bool m_hasExploded{ false };
  Nc::Point m_explosionCells[s_maxExplosionCells]{};
  int m_explosionCount{ 0 };

  void update();
};

#endif