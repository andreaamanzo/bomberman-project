#ifndef BOMB_HPP
#define BOMB_HPP

#include "Entity.hpp"
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
  Bomb(int x, int y, int radius = 1);

  Status getStatus();
  int getRadius() const;
  
private:
  using Clock = std::chrono::steady_clock;
  
  inline const static Nc::Color s_color1{ Nc::Color::Orange };
  inline const static Nc::Color s_color2{ Nc::Color::Yellow };
  inline const static Nc::Sprite2x3 s_bombSprite{ " ╽ ", "(●)", s_color1 };
  inline const static std::chrono::milliseconds s_placementTime{ 4000 };    // 3 secondi
  inline const static std::chrono::milliseconds s_explosionTime{ 1000 };    // 1 secondi
  inline const static std::chrono::milliseconds s_switchColorTime{ 400 };   // 0.4 secondi
  
  int m_radius{ 0 };
  Status m_status{ Status::Finished };
  Clock::time_point m_startTime{};
  Clock::time_point m_lastColorSwitch{};
  bool m_useFirstColor{ true };

  void update();
};

#endif