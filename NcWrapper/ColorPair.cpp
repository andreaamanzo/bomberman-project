#include "ColorPair.hpp"

namespace Nc
{
  static short toNcurses(Color c)
  {
    switch (c)
    {
    case Color::Black:   return COLOR_BLACK;
    case Color::Red:     return COLOR_RED;
    case Color::Green:   return COLOR_GREEN;
    case Color::Yellow:  return COLOR_YELLOW;
    case Color::Blue:    return COLOR_BLUE;
    case Color::Magenta: return COLOR_MAGENTA;
    case Color::Cyan:    return COLOR_CYAN;
    case Color::White:   return COLOR_WHITE;
    case Color::Default: return -1;
    }
    return -1;
  }

  short getColorPair(Color fg, Color bg)
  {
    for (auto& cp : s_colorPairs)
      if (cp.fg == fg && cp.bg == bg)
        return cp.pairId;

    short id{ s_nextPairId };
    init_pair(id, toNcurses(fg), toNcurses(bg));

    s_colorPairs[s_nextPairId] =  { fg, bg, id };
    ++s_nextPairId;
    return id;
  }
}