#include "ScoreBoard.hpp"
#include "NcWrapper.hpp"

#include <cstring>
#include <fstream>

ScoreBoard::ScoreBoard(const char* filePath)
{
  // leggo dal file state/scoreboard.txt
  std::ifstream file{ filePath };

  if (!file)
  {
    std::ofstream create(filePath); // crea file vuoto
    create.close();

    file.open(filePath); // riapre in lettura
  }

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

int ScoreBoard::getSize() { return m_size; }

// funzione per rimuovere eventuali spazi bianchi iniziali
const char* stringPolish(const char* toPolish)
{
  while (*toPolish == ' ') toPolish++;

  return toPolish;
}

// push in ordine decrescente
void ScoreBoard::pushOrderly(const char* playerName, const int score)
{
  Node* foo = new Node;
  strncpy(foo -> playerName, stringPolish(playerName), s_maxNameLenght - 1);
  foo -> playerName[s_maxNameLenght - 1] = '\0'; // assicuro che l'ultimo char sia nullchar
  foo -> score = score;
  m_size++;
  
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

// mostra la classifica e controlla se l'utente preme esc/Q
// quando l'utente preme esc/Q funzione termina -> torna al menu
void ScoreBoard::drawScoreboard(int numberPlayers)
{
  int startX{ (m_window.getWidth() - 30) / 2 };
  
  if (numberPlayers > getSize()) numberPlayers = getSize();
  int offset{ 0 };
  bool running{ true };
  while (running)
  {
    Nc::Key key = Nc::getKeyPressed();
    if (key == Nc::Key::Q || key == Nc::Key::Escape) running = false;
    if (key == Nc::Key::Down && numberPlayers - offset > s_maxVisiblePlayers) offset++;
    if (key == Nc::Key::Up && offset > 0) offset--;
    
    m_window.clear();
    
    int startY{ 1 };
    char buff[s_maxNameLenght * 3];
    snprintf(buff, sizeof(buff), "%-8s%-17s%s", "[N°]", "[NAME]", "[SCORE]");
    m_window.write(buff, startX, startY++);
    startY++; // stacco dopo i titoli
    
    Node* node = m_head;
    for (int i{ 0 }; i < offset; i++) // passo i nodi da non considerare
    {
      if (node != nullptr) node = node -> next;
    }

    int playersShown{ offset };
    while (playersShown++ < numberPlayers && node != nullptr)
    {
      // -8 -> allineamento a sx
      // -17 -> allineamento a sx (copre 17 char)
      snprintf(buff, sizeof(buff), "%-8d%-17s%d", playersShown, node -> playerName, node -> score);
  
      m_window.write(buff, startX, startY++);
      m_window.write("--------------------------------", startX-1, startY++);
  
      node = node -> next;
    }
    
    m_window.display();
    Nc::sleepFor(20);
  }

}

void ScoreBoard::saveToFile(const char* filePath)
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

// chiede quante posizioni vedere nella classifica
void ScoreBoard::show()
{
  m_window.setTitle("SCOREBOARD");

  m_window.write("How many scoreboard entries do you want to see?", 1, 1);
  m_window.write("> ", 1, 3);
  m_window.display(); 

  // gestione input del giocatore
  char buffer[64]{};
  int showPlayers{};
  bool show{ false };
  do
  {
    show = m_window.getUserInput(3, 3, buffer, sizeof(buffer));
    showPlayers = std::atoi(buffer);
  } while (show && showPlayers <= 0);

  if (show) drawScoreboard(showPlayers);

  m_window.clear();
}