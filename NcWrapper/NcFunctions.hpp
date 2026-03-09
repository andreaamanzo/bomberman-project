#ifndef NC_HELPERS_H
#define NC_HELPERS_H

#include "NcTypes.hpp"
#include <chrono>

namespace Nc
{
  void init();
  void stop();
  int getTerminalWidth();
  int getTerminalHeight();
  Key getKeyPressed();
  void sleepFor(int milliseconds);
}

#endif