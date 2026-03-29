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
  using enum Direction;

  switch (dir)
  {
    case Up:    return Down;
    case Down:  return Up;
    case Right: return Left;
    case Left:  return Right;
    default:    return None;
  }
}

#endif