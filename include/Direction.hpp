#ifndef DIRECTION_HPP
#define DIRECTION_HPP

enum class Direction
{
  None,
  Up,
  Down,
  Right,
  Left
};

inline Direction getOppositeDir(Direction dir)
{
  switch (dir)
  {
    case Direction::Up:    return Direction::Down;
    case Direction::Down:  return Direction::Up;
    case Direction::Right: return Direction::Left;
    case Direction::Left:  return Direction::Right;
    default:               return Direction::None;
  }
}

#endif