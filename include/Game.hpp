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
  Nc::Window m_leftMenu;
  Nc::Window m_rightMenu;
  Player     m_player;
  bool m_running{ true };

  bool checkLoseConditions();
  void update();
  void render();
  void leaveCurrentLevel();
  bool initCurrentLevel();
  void goToNextLevel();
  void goToPreviousLevel();
  void handleCompletedLevel();
  void drawMessage(int displayTime, const char* message, const char* subMessage = "");
};

#endif