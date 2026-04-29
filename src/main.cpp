#include "NcWrapper.hpp"
#include "Settings.hpp"
#include "ScoreList.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include <iostream>
#include <cstdlib>

int main() 
{
  Nc::init();
  
  // grandezza minima
  Nc::checkTerminalSize(Settings::mapWidth + Settings::menuWidth*2 + 6, Settings::mapHeight); 

  int w_startx = (Nc::getTerminalWidth()  - Settings::mapWidth) / 2;
  int w_starty = (Nc::getTerminalHeight() - Settings::mapHeight) / 2;

  Nc::Window window{ Settings::mapWidth, Settings::mapHeight, w_startx, w_starty };

  Menu menu{};
  ScoreList scoreBoard{ "state/scoreboard.txt" };
  
  constexpr int numLevels{ 5 };
  const char* paths[numLevels]{ 
    "levels/level_01.txt", 
    "levels/level_02.txt", 
    "levels/level_03.txt", 
    "levels/level_04.txt", 
    "levels/level_05.txt" 
  };

  bool running = true;
  Menu::Option option = Menu::Option::Menu;

  while (running)
  {
    switch (option)
    {
    case Menu::Option::Close :
      running = false;
      break;
    
    case Menu::Option::Menu:
      option = menu.getMenuOption();
      
    case Menu::Option::Game:
    {
      Game game{ numLevels, paths };
      int score = game.play();
      
      // chiede nome e aggiorna scoreboard
      window.setTitle("END GAME");

      window.write("Enter your name:", 1, 1);
      window.write("> ", 1, 3);
      window.display();

      // gestione input del giocatore
      char buffer[15];
      do
      {
        window.getUserInput(3, 3, buffer, sizeof(buffer));
      } while (buffer[0] == '\0');
      
      scoreBoard.pushOrderly(buffer, score);
      scoreBoard.saveToFile("state/scoreboard.txt");
      
      window.clear();
      
      option = Menu::Option::Scoreboard;
      break;
    }
    case Menu::Option::Scoreboard:
      // show scoreboard
      // 1) chiede numero di giocatori da visualizzare 
      // 2) while che mostra semplicemente la classifica + controlla se l'utente preme esc/Q
      // 3) quando l'utente preme esc funzione termina -> dobbiamo tornare al menu
      window.setTitle("SCOREBOARD");

      window.write("How many scoreboard entries do you want to see?", 1, 1);
      window.write("> ", 1, 3);
      window.display(); 

      // gestione input del giocatore
      char buffer[64];
      window.getUserInput(3, 3, buffer, sizeof(buffer));
      int showPlayers = std::atoi(buffer);

      if(showPlayers > 0) scoreBoard.drawScoreboard(showPlayers, window);
      
      option = Menu::Option::Menu;
      break;
    } 
  }

  Nc::stop();
}

