#ifndef COLOR_PAIR_HPP
#define COLOR_PAIR_HPP

#include "NcTypes.hpp"
#include <ncurses.h>

namespace Nc
{
  struct ColorPair
  {
    Color fg;
    Color bg;
    short pairId;
  };

  short getColorPair(Color fg, Color bg);
}


#endif