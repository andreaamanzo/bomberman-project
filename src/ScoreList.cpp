#include "ScoreList.hpp"
#include "NcWrapper.hpp"

#include <cstring>
#include <fstream>

ScoreList::ScoreList(const char* filePath)
{
  // leggo dal file state/scoreboard.txt
  std::ifstream file{ filePath };

  if (!file.is_open())
  {
    Nc::stopWithError(1, "Scoreboard loading failed: file not opened correctly");
  }

  int playerScore;
  char nameBuffer[s_maxNameLenght];
  while (file >> playerScore)
  {
    file >> std::ws; // salta ogni spazio bianco prima del nome
    
    file.getline(nameBuffer, s_maxNameLenght); // permette di avere spazi bianchi nel nome del giocatore

    pushOrderly(nameBuffer, playerScore);
  }

  file.close();
}

void ScoreList::pushOrderly(const char* playerName, int score)
{
  Node* foo = new Node;
  strncpy(foo -> playerName, playerName, s_maxNameLenght - 1);
  foo -> playerName[s_maxNameLenght - 1] = '\0'; // assicuro che l'ultimo char sia nullchar
  foo -> score = score;
  
  if (m_head == nullptr)
  {  
    m_head = foo;
  }
  else if (m_head -> score < score)
  {
    foo -> next = m_head;
    m_head = foo;
  }
  else
  {
    Node* check = m_head;
    while (check -> next != nullptr)
    {
      if ((check -> next) -> score < score)
      {
        foo -> next = check -> next;
        check -> next = foo;
        return;
      }
      check = check -> next;
    }
    check -> next = foo;
  }
}

void ScoreList::drawScoreboard(int numberPlayers, Nc::Window& window, int x, int y)
{
  window.write("NAME |\t | SCORE", x, y++);

  Node* node = m_head;
  while (numberPlayers-- > 0 && node != nullptr)
  {
    char buff[s_maxNameLenght * 2];
    sprintf(buff, "%s\t%d", node -> playerName, node -> score);

    window.write(buff, x, y++);

    node = node -> next;
  }
}

void ScoreList::saveToFile(const char* filePath)
{
  std::ofstream file{ filePath };

  if (!file.is_open())
  {
    Nc::stopWithError(1, "Scoreboard saving failed: file not opened correctly");
  }

  Node* node = m_head;
  while (node != nullptr)
  {
    file << node -> score << " " << node -> playerName << '\n';
    
    node = node -> next;
  }

  file.close();
}