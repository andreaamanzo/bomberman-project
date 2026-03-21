#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "NcWrapper.hpp"
#include "Settings.hpp"
#include "Bomb.hpp"
#include "Player.hpp"
#include "Item.hpp"

class Level 
{
public:
  Level(int levelNumber, const char* mapFilePath); 

  void drawWalls(Nc::Window& window) const;
  void drawEnemies(Nc::Window& window) const;
  void drawBombs(Nc::Window& window) const;
  void drawItems(Nc::Window& window) const;
  bool checkWallCollision(const Entity& entity) const;
  
  // Se il player si trova su un item, qusto viene returnato, sennò return item nullo
  Item collectItem(const Player& player); 

  void moveEnemies();
  void addBomb(const Bomb& bomb);

  // gestisce automaticamente esplosioni di muri e nemici, return true se colpisce il player
  bool handleBombsExplosion(const Player& player); 

  int  getLevelNumber() const;

  // Funzioni per la gestione del tempo
  //...
  void pause(); // mette il livello in pausa
  void start(); // opposto a pause

private:
  enum class Tile
  {
    Empty,
    Wall,
    BreakableWall,
  };

  inline const static Nc::Sprite2x3 s_wallSprite{ "███", "███", Nc::Color::White };
  inline const static Nc::Sprite2x3 s_breakableWallSprite{ "▚▞▚", "▚▞▚", Nc::Color::White };

  int m_levelNumber{};
  Tile m_map[Settings::mapRows][Settings::mapCols];
  // List<Bomb> m_bombs;
  // List<Enemy> m_enemies;
  // List<Item> m_items;

  // Membri per la gestione del tempo (tempo inizile + tempo totale o tempo rimanente)
};

#endif