#ifndef NC_HELPERS_H
#define NC_HELPERS_H

#include "NcTypes.hpp"

namespace Nc
{
  void init();
  void stop();
  void stopWithError(int exitCode, const char* msg);
  int getTerminalWidth();
  int getTerminalHeight();
  void checkTerminalSize(int minWidth, int minHeight);
  Key getKeyPressed();
  void sleepFor(int milliseconds);
}

#endif