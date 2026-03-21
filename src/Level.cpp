#include "Level.hpp"
#include "NcFunctions.hpp"
#include "Settings.hpp"
#include "Window.hpp"
#include <fstream>
#include <iostream>
#include <string>

Level::Level(
    int levelNumber,
    const char *mapFilePath) // utilizzata ai per imparare utilizzo ifstram e
                             // capire utilizzo generale delle librerie
    : m_levelNumber{levelNumber} {
  // aprire il file al path passato, parsarlo e inizializzare m_map
  // leggo il file con ifstram
  std::ifstream file(mapFilePath);
  // controllo se il file è stato aperto correttamente
  if (!file.is_open()) {
    Nc::stop();
    std::cerr << "Map file not found" << std::endl;
    std::exit(1);
  }
  char c;
  int nrow = 0;
  int nchar = 0;
  // inizializzazione e parsing mappa
  while (file.get(c)) {
    if (c == '\n') {
      nrow++;
      nchar = 0;
      if (nrow > Settings::mapRows) {
        Nc::stop();
        std::cerr << "Invalid map" << std::endl;
        std::exit(1);
        continue;
      }
    } else {
      if (c == 'X')
        m_map[nrow][nchar] = Tile::Wall;
      else if (c == '#')
        m_map[nrow][nchar] = Tile::BreakableWall;
      // else if (c == 'O') m_map[nrow][nchar] = Tile::Door;
      else
        m_map[nrow][nchar] = Tile::Empty;
      nchar++;
      if (Settings::mapCols > 30) {
        Nc::stop();
        std::cerr << "Invalid map" << std::endl;
        std::exit(1);
      }
    }
  }
  file.close();
}

void Level::drawWalls(Nc::Window &window) const {
  for (int y = 0; y < Settings::mapRows; y++) {
    for (int x = 0; x < Settings::mapCols; x++) {
      int drawX = x * Settings::entityWidth;
      int drawY = y * Settings::entityHeight;

      if (m_map[y][x] == Tile::Wall)
        window.draw(s_wallSprite, drawX, drawY);
      else if (m_map[y][x] == Tile::BreakableWall)
        window.draw(s_breakableWallSprite, drawX, drawY);
    }
  }
}