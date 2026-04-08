#ifndef SETTINGS_HPP
#define SETTINGS_HPP

namespace Settings
{
  constexpr int entityHeight{ 2 };
  constexpr int entityWidth{ 3 };
  constexpr int mapCols{ 40 };
  constexpr int mapRows{ 20 };
  constexpr int mapHeight{ entityHeight * mapRows };
  constexpr int mapWidth{ entityWidth * mapCols };
  constexpr int menuWidth{ mapWidth/4};
}

#endif