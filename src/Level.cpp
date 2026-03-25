#include "Level.hpp"
#include "Bomb.hpp"
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

void Level::addBomb(Bomb& bomb)
{
  if (m_bombsSize >= s_maxLengthArrays)
    Nc::stopWithError(1, "Bombs array capacity exceeded.");

  while (bomb.getX() % Settings::entityWidth != 0)
    bomb.setPos(bomb.getX() + 1, bomb.getY());

  while (bomb.getY() % Settings::entityHeight != 0)
    bomb.setPos(bomb.getX(), bomb.getY() + 1);

  m_bombs[m_bombsSize++] = bomb;
}

void Level::handleBombExplosion(const Bomb& bomb)
{
  int r = bomb.getRadius();
  int x = bomb.getX() / Settings::entityWidth;
  int y = bomb.getY() / Settings::entityHeight;

  const int dirs[4][2] {
    { 1,  0 },   // right
    {-1,  0 },   // left
    { 0, -1 },   // up
    { 0,  1 }    // down
  };

  for (int d = 0; d < 4; d++)
  {
    for (int j = 1; j <= r; j++)
    {
      int nx = x + dirs[d][0] * j;
      int ny = y + dirs[d][1] * j;

      Tile& tile = m_map[ny][nx];

      if (tile == Tile::Wall)
        break;

      if (tile == Tile::BreakableWall)
      {
        tile = Tile::Empty;
        break;
      }
    }
  }
}

void Level::drawBombExplosion(const Bomb& bomb, Nc::Window& window)
{
  int r = bomb.getRadius();
  int x = bomb.getX() / Settings::entityWidth;
  int y = bomb.getY() / Settings::entityHeight;

  const int dirs[4][2] {
    { 1,  0 },   // right
    {-1,  0 },   // left
    { 0, -1 },   // up
    { 0,  1 }    // down
  };

  window.draw(s_explosionSprite, x * Settings::entityWidth, y * Settings::entityHeight);

  for (int d = 0; d < 4; d++)
  {
    for (int j = 1; j <= r; j++)
    {
      int nx = x + dirs[d][0] * j;
      int ny = y + dirs[d][1] * j;

      Tile& tile = m_map[ny][nx];

      if (tile == Tile::Wall)
        break;

      if (tile == Tile::BreakableWall)
      {
        window.draw(s_explosionSprite, nx * Settings::entityWidth, ny * Settings::entityHeight);
        break;
      }

      if (tile == Tile::Empty)
        window.draw(s_explosionSprite, nx * Settings::entityWidth, ny * Settings::entityHeight);
    }
  }
}

bool Level::handleBombs(Player& player)
{
  // manca da controllare la collisone con il player
  bool hitPlayer = false;

  for (int i = 0; i < m_bombsSize; i++)
  {
    Bomb& bomb = m_bombs[i];
    switch (bomb.getStatus())
    {
    case Bomb::Status::Placed:
      break;

    case Bomb::Status::Exploding:
      break;

    case Bomb::Status::Finished:
      handleBombExplosion(bomb);

      m_bombsSize--;
      for (int j = i; j < m_bombsSize; j++)
        m_bombs[j] = m_bombs[j+1];

      player.restoreBomb();
      break;      
    }
  }

  return hitPlayer;
} 

void Level::drawBombs(Nc::Window& window)
{
  for (int i = 0; i < m_bombsSize; i++)
  {
    Bomb& bomb = m_bombs[i];
    switch (bomb.getStatus())
    {
    case Bomb::Status::Placed:
      bomb.draw(window);
      break;

    case Bomb::Status::Exploding:
      drawBombExplosion(bomb, window);
      break;

    case Bomb::Status::Finished:
      break;
    }
  }
}

int Level::getLevelNumber() const
{
  return m_levelNumber;
}