#ifndef SCORELIST_HPP
#define SCORELIST_HPP

class ScoreList
{
public:
  ScoreList(const char* playerName, const int score);

  void push(const char* playerName, const int score);

private:
  struct Node
  {
    const char* m_playerName;
    const int m_score{ 0 };
    Node* next{ nullptr };
  };

  Node* m_head{ nullptr };

};

#endif