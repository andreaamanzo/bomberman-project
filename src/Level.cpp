#include "Level.hpp"
#include "Bomb.hpp"
#include "Enemy.hpp"
#include "LevelList.hpp"
#include "Player.hpp"
#include "Settings.hpp"
#include "NcWrapper.hpp"
#include "Direction.hpp"
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
      switch (c)
      {
      case 'X':
        m_map[nrow][nchar] = Tile::Wall;
        break;
      case '#':
        m_map[nrow][nchar] = Tile::BreakableWall;
        break;
      case 'O':
        m_map[nrow][nchar] = Tile::DoorNext;
        m_doorNextPos = { nchar * Settings::entityWidth, nrow * Settings::entityHeight };
        break;
      case 'P':
        m_map[nrow][nchar] = Tile::DoorPrev;
        m_doorPrevPos = { nchar * Settings::entityWidth, nrow * Settings::entityHeight };
        break;
      case '1':
        m_enemies[m_enemiesSize++] = Enemy(Enemy::Type::First_Enemy, nchar * Settings::entityWidth, nrow * Settings::entityHeight);
        m_map[nrow][nchar] = Tile::Empty;        
        break;        
      case '2':
        m_enemies[m_enemiesSize++] = Enemy(Enemy::Type::Second_Enemy, nchar * Settings::entityWidth, nrow * Settings::entityHeight);
        m_map[nrow][nchar] = Tile::Empty;
        break;        
      default:
        m_map[nrow][nchar] = Tile::Empty;
        break;
      }

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

      else if (m_map[y][x] == Tile::DoorNext)
        window.draw(s_doorNextSprite, drawX, drawY);
      
      else if (m_map[y][x] == Tile::DoorPrev)
        window.draw(s_doorPrevSprite, drawX, drawY);

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

bool Level::shouldGoNextLevel() const
{
  return m_shouldGoNext;
}

bool Level::shouldGoPrevLevel() const
{
  return m_shouldGoPrev;
}

Nc::Point Level::getDoorPrevPos() const
{
  return m_doorPrevPos;
}

Nc::Point Level::getDoorNextPos () const
{
  return m_doorNextPos;
}

bool Level::checkIsWall(int x, int y) const
{
  return 
    m_map[y][x] == Tile::Wall || 
    m_map[y][x] == Tile::BreakableWall ||
    m_map[y][x] == Tile::DoorNext ||
    m_map[y][x] == Tile::DoorPrev;
}

bool Level::checkWallCollision(const Entity& entity) const
{
  int width{ Settings::entityWidth };
  int height{ Settings::entityHeight };

  int x = entity.getX();
  int y = entity.getY();

  if (checkIsWall(x / width, y / height)) return true;

  if (x % width != 0 && y % height != 0)
    if (checkIsWall(x / width + 1, y / height + 1)) return true;

  if (x % width != 0)
    if (checkIsWall(x / width + 1, y / height)) return true;

  if (y % height != 0)
    if (checkIsWall(x / width, y / height + 1)) return true;
  
  return false;
}

bool Level::checkDoorNextCollision(const Entity& entity) const
{
  Entity door{ m_doorNextPos.x, m_doorNextPos.y };
  // std::cerr << door.getX() << " " << door.getY() << "\n";
  return entity.collide(door);
}

bool Level::checkDoorPrevCollision(const Entity& entity) const
{
  Entity door{ m_doorPrevPos.x, m_doorPrevPos.y };
  return entity.collide(door);
}

void Level::movePlayer(Player& player, Direction dir)
{
  player.move(dir);
    
  if (checkDoorNextCollision(player))
    m_shouldGoNext = true;
  else 
    m_shouldGoNext = false;

  if (checkDoorPrevCollision(player))
    m_shouldGoPrev = true;
  else 
    m_shouldGoPrev = false;

  if (checkWallCollision(player))
    player.move(getOppositeDir(dir));

  // TODO controllare le collisioni con i nemici / bombe
}

void Level::start()
{
  m_shouldGoNext = false;
  m_shouldGoPrev = false;

  // start tempo e altra roba (?)
}

void Level::pause()
{
  // stop del tempo
}

void Level::drawEnemies(Nc::Window& window) const {
  for (int i = 0; i < m_enemiesSize; i++)
  {
    const Enemy& enemy = m_enemies[i];  
    enemy.draw(window);
  }
}

void Level::moveEnemies(){
}