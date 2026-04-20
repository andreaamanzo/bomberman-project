#include "NcWrapper.hpp"
#include "Settings.hpp"
#include "ScoreList.hpp"
#include "Game.hpp"
#include <iostream>

int main() 
{
  Nc::init();
  
  // grandezza minima
  Nc::checkTerminalSize(Settings::mapWidth + Settings::menuWidth*2 + 6, Settings::mapHeight); 

  int w_startx = (Nc::getTerminalWidth()  - Settings::mapWidth) / 2;
  int w_starty = (Nc::getTerminalHeight() - Settings::mapHeight) / 2;
  
  Nc::Window window{ Settings::mapWidth, Settings::mapHeight, w_startx, w_starty };
  window.setTitle("BOMBERMAN MENU");
  
  constexpr int numLevels{ 5 };
  const char* paths[numLevels]{ 
    "levels/level_01.txt", 
    "levels/level_02.txt", 
    "levels/level_03.txt", 
    "levels/level_04.txt", 
    "levels/level_05.txt" 
  };

  bool running = true;
  int option = 2;

  while (running)
  {
    switch (option)
    {
    case 0:
      running = false;
      break;
    case 1:
      window.clear();
      window.display();
      // TODO menu -> get option
      option = 0;
      break;
    case 2:
    {
      Game game{ numLevels, paths };
      int score = game.play();
      // chiede nome e aggiorna scoreboard
      option = 3;
      break;
    }
    case 3:
      // show scoreboard -> 
      //  1) chiede numero di giocatori da visualizzare 
      //  2) while che mostra semplicemente la classifica + controlla se l'utente preme esc/Q
      //  3) quando l'utente preme esc funzione termina -> dobbiamo tornare al menu

      // ! test scoreboard (dovrà essere una funzione come sopra)
      // ScoreList test{ "state/scoreboard.txt" };
      // test.drawScoreboard(100, window, 10, 2);
      // window.display();

      option = 1;
      break;
    } 
  }

  Nc::stop();
}

