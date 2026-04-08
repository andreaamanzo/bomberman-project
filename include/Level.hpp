#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "NcWrapper.hpp"
#include "Settings.hpp"
#include "Bomb.hpp"
#include "Player.hpp"
#include "Item.hpp"
#include "Enemy.hpp"
#include "Direction.hpp"
#include <chrono>

class Level 
{
public:
  Level(int levelNumber, const char* mapFilePath); 

  void drawWalls(Nc::Window& window) const;
  void drawEnemies(Nc::Window& window) const;
  void drawBombs(Nc::Window& window);
  void drawItems(Nc::Window& window) const;
  bool checkWallCollision(const Entity& entity) const;
  bool checkDoorNextCollision(const Entity& entity) const;
  bool checkDoorPrevCollision(const Entity& entity) const;
  bool shouldGoNextLevel() const;
  bool shouldGoPrevLevel() const;
  Nc::Point getDoorPrevPos() const;
  Nc::Point getDoorNextPos () const;

  // restituisce l'item alle coordinate passate, se non c'è nessun item return item nullo
  Item getItem(const Entity& entity);

  void moveEnemies();
  void movePlayer(Player& player, Direction dir);

  void addBomb(Bomb& bomb);

  // gestisce automaticamente esplosioni di muri e nemici, e hit player
  void handleBombs(Player& player); 
  void handleEnemies(Player &player);

  bool isFinished() const;

  int  getLevelNumber() const;

  // Funzioni per la gestione del tempo
  //...
  void pause(); // mette il livello in pausa
  void start(); // opposto a pause
  void updateTime();
  bool checkTimeFinished();
  int getTimeLeftSec() const;

private:
  using Clock = std::chrono::steady_clock;
  using Mills = std::chrono::milliseconds;

  enum class Tile
  {
    Empty,
    Wall,
    BreakableWall,
    DoorNext,
    DoorPrev,
  };

  inline const static Nc::Sprite2x3 s_wallSprite{ "███", "███", Nc::Color::White };
  inline const static Nc::Sprite2x3 s_breakableWallSprite{ "▚▞▚", "▚▞▚", Nc::Color::White };
  inline const static Nc::Sprite2x3 s_explosionSprite{ "███", "███", Nc::Color::Fire };
  inline const static Nc::Sprite2x3 s_doorNextSprite{ "-⌼-", "-⌼-", Nc::Color::Sky, Nc::Color::Black };
  inline const static Nc::Sprite2x3 s_doorPrevSprite{ "-▣-", "-▣-", Nc::Color::Magenta, Nc::Color::Black };

  inline constexpr static int s_maxLengthArrays{ 64 };

  int m_levelNumber{};
  Tile m_map[Settings::mapRows][Settings::mapCols];
  Nc::Point m_doorPrevPos;
  Nc::Point m_doorNextPos;
  bool m_shouldGoNext{ false };
  bool m_shouldGoPrev{ false };
  bool m_isPaused{ true };

  // Membri per la gestione del tempo (tempo iniziale + tempo totale o tempo rimanente)
  Mills m_timeLeft{ 180 * 1000 };
  Clock::time_point m_lastUpdate{};

  Bomb  m_bombs[s_maxLengthArrays]{};
  int   m_bombsSize{ 0 };
  Item  m_items[s_maxLengthArrays]{};
  int   m_itemsSize{ 0 };
  Enemy m_enemies[s_maxLengthArrays]{};
  int   m_enemiesSize{ 0 };

  void setExplosionCells(Bomb& bomb) const;
  void applyExplosion(const Bomb& bomb, Player &player) ;
  void drawExplosion(const Bomb& bomb, Nc::Window& window);
  bool checkIsWall(int x, int y) const;
};


#endif