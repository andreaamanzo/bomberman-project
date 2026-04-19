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

  Bomb();
  Bomb(int x, int y, int radius = 1, bool isEnemy = false);

  Status getStatus();
  int getRadius() const;
  bool hasExploded() const;
  void setExploded(bool set);
  const Nc::Point* getExplosionCells() const;
  int getExplosionCount() const;
  void setExplosionCells(const Nc::Point cells[], int count);
  bool isEnemy() const;
  
  inline constexpr static int s_maxExplosionCells{ Settings::mapCols + Settings::mapRows };

private:
  using Clock = std::chrono::steady_clock;
  
  inline const static Nc::Color s_color1{ Nc::Color::Orange };
  inline const static Nc::Color s_color2{ Nc::Color::Yellow };
  inline const static Nc::Color s_ecolor1{ Nc::Color::Green };
  inline const static Nc::Color s_ecolor2{ Nc::Color::Red };
  inline const static Nc::Sprite2x3 s_bombSprite{ " ╽ ", "(●)", s_color1 };
  inline const static std::chrono::milliseconds s_placementTime{ 3000 };    // 3 secondi
  inline const static std::chrono::milliseconds s_explosionTime{ 500 };     // 0.5 secondi
  inline const static std::chrono::milliseconds s_switchColorTime{ 400 };   // 0.4 secondi
  inline const static Nc::Sprite2x3 s_enemyBombSprite{ " ◉ ", "[#]", s_ecolor1 };


  
  int m_radius{ 0 };
  Status m_status{ Status::Finished };
  Clock::time_point m_startTime{};
  Clock::time_point m_lastColorSwitch{};
  bool m_useFirstColor{ true };
  bool m_hasExploded{ false };
  Nc::Point m_explosionCells[s_maxExplosionCells]{};
  int m_explosionCount{ 0 };
  bool m_isEnemy{ false };

  void update();
};

#endif