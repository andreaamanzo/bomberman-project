#ifndef GAME_HPP
#define GAME_HPP

#include "NcWrapper.hpp"
#include "Player.hpp"
#include "LevelList.hpp"

class Game
{
public:
  Game(int numLevels, const char* levelPaths[]);

  int play();

private:
  LevelList  m_levelList;
  Level*     m_currLevel;
  Nc::Window m_mainWindow;
  Nc::Window m_playerMenu;
  Nc::Window m_itemsMenu;
  Nc::Window m_levelMenu;
  Nc::Window m_controlsMenu;
  Player     m_player;
  bool m_running{ true };

  bool checkLoseConditions();
  void writeTimedItems();
  void writeOnMenus();
  void update();
  void render();
  void leaveCurrentLevel();
  bool initCurrentLevel();
  void goToNextLevel();
  void goToPreviousLevel();
  void handleCompletedLevel();
  void drawMessage(const char* message, const char* subMessage = "");
};

#endif