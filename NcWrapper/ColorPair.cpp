#include "ColorPair.hpp"
#include "NcTypes.hpp"

namespace Nc
{
  static short toNcurses(Color c)
  {
    switch (c)
    {
    case Color::Black:     return COLOR_BLACK;
    case Color::Red:       return COLOR_RED;
    case Color::Green:     return COLOR_GREEN;
    case Color::Yellow:    return COLOR_YELLOW;
    case Color::Blue:      return COLOR_BLUE;
    case Color::Magenta:   return COLOR_MAGENTA;
    case Color::Cyan:      return COLOR_CYAN;
    case Color::White:     return COLOR_WHITE;

    case Color::Orange:    return 8;
    case Color::DarkGray:  return 9;
    case Color::LightGray: return 10;
    case Color::Pink:      return 11;
    case Color::Lime:      return 12;
    case Color::Sky:       return 13;
    case Color::Purple:    return 14;
    case Color::Gold:      return 15;
    case Color::Fire:      return 16;

    case Color::Default:   return -1;
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