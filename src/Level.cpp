#include "Level.hpp"
#include "NcFunctions.hpp"
#include "Settings.hpp"
#include "Window.hpp"
#include <fstream>
#include <iostream>

// ALE: utilizzata ai per imparare utilizzo ifstram e capire utilizzo generale delle librerie
Level::Level(int levelNumber, const char* mapFilePath) 
  : m_levelNumber{ levelNumber } 
{
  // leggo il file con ifstram
  std::ifstream file{ mapFilePath };

  // controllo se il file è stato aperto correttamente, sennò exit
  if (!file.is_open())
    Nc::stopWithError(1, "Level loading failed: map file not found.");

  // parsing del file e inizializzazione mappa
  char c;
  int nrow = 0;
  int nchar = 0;

  while (file.get(c)) 
  {
    if (nrow >= Settings::mapRows || nchar > Settings::mapCols) 
      Nc::stopWithError(1, "Invalid map: exceeds maximum allowed size.");

    if (c == '\n') 
    {
      if (nchar < Settings::mapCols)
        Nc::stopWithError(1, "Invalid map: incorrect number of columns.");

      nrow++;
      nchar = 0;
    } 
    else 
    {
      if (c == 'X')
        m_map[nrow][nchar] = Tile::Wall;
      else if (c == '#')
        m_map[nrow][nchar] = Tile::BreakableWall;
      // else if (c == 'O') m_map[nrow][nchar] = Tile::Door;
      else
        m_map[nrow][nchar] = Tile::Empty;

      nchar++;
    }
  }

  // controllo numero caratteri ultima riga
  if (nchar < Settings::mapCols)
    Nc::stopWithError(1, "Invalid map: incorrect number of columns.");

  // controllo numero righe
  if (nrow != Settings::mapRows - 1)
    Nc::stopWithError(1, "Invalid map: incorrect number of rows.");

  file.close();
}

void Level::drawWalls(Nc::Window &window) const 
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