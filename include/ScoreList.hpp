#ifndef SCORELIST_HPP
#define SCORELIST_HPP

#include "NcWrapper.hpp"

class ScoreList
{
public:
  ScoreList(const char* filePath);

  // push in ordine decrescente
  void pushOrderly(const char* playerName, const int score);
  void drawScoreboard(int numberPlayers, Nc::Window& window, int x, int y);
  void saveToFile(const char* filePath);

private:
  // constexpr: nota a compile time poichè len di array
  // static: comune ad ogni istanza di classe, non copiata
  static constexpr int s_maxNameLenght{ 64 };

  struct Node
  {
    char playerName[s_maxNameLenght];
    int score{ 0 };
    Node* next{ nullptr };
  };

  Node* m_head{ nullptr };
};

#endif