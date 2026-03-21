#include "Level.hpp"
#include "Settings.hpp"

Level::Level(int levelNumber, const char* mapFilePath)
  : m_levelNumber{ levelNumber }
{ 
  // aprire il file al path passato, parsarlo e inizializzare m_map

  // esempio per vedere qualche muro, poi da togliere :

  for (int y = 0; y < Settings::mapRows; y++)
  {
    for (int x = 0; x < Settings::mapCols; x++)
    {
      m_map[y][x] = Tile::Empty;
    }
  }

  m_map[0][0] = Tile::Wall;
  m_map[Settings::mapRows - 1][0] = Tile::Wall;
  m_map[10][11] = Tile::Wall;
  m_map[5][9] = Tile::BreakableWall;
}

void Level::drawWalls(Nc::Window& window) const
{
  for (int y = 0; y < Settings::mapRows; y++)
  {
    for (int x = 0; x < Settings::mapCols; x++)
    {
      int drawX = x * Settings::entityWidth;
      int drawY = y * Settings::entityHeight;

      if (m_map[y][x] == Tile::Wall)
        window.draw(s_wallSprite, drawX, drawY);
      else if (m_map[y][x] == Tile::BreakableWall)
        window.draw(s_breakableWallSprite, drawX, drawY);
    }
  }
}