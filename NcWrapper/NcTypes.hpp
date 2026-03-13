#ifndef NC_TYPES_H
#define NC_TYPES_H

namespace Nc
{
  enum class Key 
  {
    None,

    Up,
    Down,
    Left,
    Right,

    Enter,
    Escape,
    Space,
    Backspace,

    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
  };

  enum class Color
  {
    Default,
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White
  };

  struct Point
  {
    int x{};
    int y{};
  };
}

#endif