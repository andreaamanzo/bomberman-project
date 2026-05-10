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
      break;
      
    case Menu::Option::Game:
    {
      Game game{ numLevels, paths };
      int score = game.play();
      
      game.enterPlayerName(window, scoreBoard, score);
      
      option = Menu::Option::Scoreboard;
      break;
    }
    case Menu::Option::Scoreboard:
    
      scoreBoard.show();

      option = Menu::Option::Menu;
      break;
    }
  }

  Nc::stop();
}
