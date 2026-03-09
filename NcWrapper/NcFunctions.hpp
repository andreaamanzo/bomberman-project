#ifndef NC_HELPERS_H
#define NC_HELPERS_H

#include "NcTypes.hpp"
#include <chrono>

namespace Nc
{
  void init();
  void stop();
  int getScreenWidth();
  int getScreenHeight();
  Key getKeyPressed();
  void sleepFor(std::chrono::milliseconds milliseconds);
}

#endif