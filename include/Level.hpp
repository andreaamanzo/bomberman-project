#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "NcWrapper.hpp"
#include "Settings.hpp"
#include "Bomb.hpp"
#include "Player.hpp"
#include "Item.hpp"
#include "Enemy.hpp"
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
  
  // restituisce l'item alle coordinate passate, se non c'è nessun item return item nullo
  Item getItem(int x, int y); 

  void moveEnemies();
  void addBomb(Bomb& bomb);

  // gestisce automaticamente esplosioni di muri e nemici, return true se colpisce il player
  bool handleBombs(Player& player); 

  int  getLevelNumber() const;

  // Funzioni per la gestione del tempo
  //...
  void pause(); // mette il livello in pausa
  void start(); // opposto a pause

private:
  using Clock = std::chrono::steady_clock;

  enum class Tile
  {
    Empty,
    Wall,
    BreakableWall,
  };

  inline const static Nc::Sprite2x3 s_wallSprite{ "███", "███", Nc::Color::White };
  inline const static Nc::Sprite2x3 s_breakableWallSprite{ "▚▞▚", "▚▞▚", Nc::Color::White };
  inline const static Nc::Sprite2x3 s_explosionSprite{ "███", "███", Nc::Color::Fire };

  inline constexpr static int s_maxLengthArrays{ 64 };

  int m_levelNumber{};
  Tile m_map[Settings::mapRows][Settings::mapCols];

  // Membri per la gestione del tempo (tempo iniziale + tempo totale o tempo rimanente)
  Clock::time_point m_startTime{};

  Bomb  m_bombs[s_maxLengthArrays]{};
  int   m_bombsSize{ 0 };
  Item  m_items[s_maxLengthArrays]{};
  int   m_itemsSize{ 0 };
  Enemy m_enemies[s_maxLengthArrays]{};
  int   m_enemiesSize{ 0 };

  void handleBombExplosion(const Bomb& bomb);
  void drawBombExplosion(const Bomb& bomb, Nc::Window& window);
};

#endif