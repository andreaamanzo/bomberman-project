#ifndef COLOR_PAIR_H
#define COLOR_PAIR_H

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

  static ColorPair s_colorPairs[64]{};
  static short s_nextPairId{ 1 };

  short getColorPair(Color fg, Color bg);
}


#endif