#ifndef SETTINGS_HPP
#define SETTINGS_HPP

namespace Settings
{
  constexpr int entityHeight{ 2 };
  constexpr int entityWidth{ 3 };
  constexpr int mapCols{ 30 };
  constexpr int mapRows{ 15 };
  constexpr int mapHeight{ entityHeight * mapRows };
  constexpr int mapWidth{ entityWidth * mapCols };
}

#endif