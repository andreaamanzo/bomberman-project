#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include "NcWrapper.hpp"
#include "Settings.hpp"

class ScoreBoard
{
public:
  ScoreBoard(const char* filePath);
  void pushOrderly(const char* playerName, const int score);
  void drawScoreboard(int numberPlayers);
  void saveToFile(const char* filePath);
  void show();
  int getSize();

private:
  // constexpr: nota a compile time poichè len di array
  // static: comune ad ogni istanza di classe, non copiata
  static constexpr int s_maxVisiblePlayers{ 19 };
  static constexpr int s_maxNameLenght{ 15 };
  int w_startx = (Nc::getTerminalWidth()  - Settings::mapWidth) / 2;
  int w_starty = (Nc::getTerminalHeight() - Settings::mapHeight) / 2;
  Nc::Window m_window{ Settings::mapWidth, Settings::mapHeight, w_startx, w_starty };
  
  struct Node
  {
    char playerName[s_maxNameLenght];
    int score{ 0 };
    Node* next{ nullptr };
  };
  
  Node* m_head{ nullptr };
  int m_size{ 0 };
};

#endif