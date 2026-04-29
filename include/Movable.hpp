#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include "Entity.hpp"
#include "Direction.hpp"
#include <chrono>

class Movable : public Entity
{
public:
  Movable() = default;
  Movable(const Nc::Sprite2x3& sprite, int x = 0, int y = 0, int delaySpeedMillisecods = 20);

  void move(Direction dir, int velocity);
  bool shouldMove();
  void setDelaySpeed(int milliseconds);
  //std::chrono::milliseconds getSpeed();

private:
  using Clock = std::chrono::steady_clock;
  using Milliseconds = std::chrono::milliseconds;

  Milliseconds m_delaySpeed{ 20 };
  Clock::time_point m_lastMoveTime{};
};

#endif