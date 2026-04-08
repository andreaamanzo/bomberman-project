#include "NcWrapper.hpp"
#include "Player.hpp"
#include "Direction.hpp"
#include "Settings.hpp"
#include "LevelList.hpp"
#include "Level.hpp"
#include "Bomb.hpp"
#include <stdio.h>

int main() 
{
  Nc::init();
  
  // la grandezza minima effettiva poi la decideremo
  Nc::checkTerminalSize(Settings::mapWidth + Settings::menuWidth*2 + 6, Settings::mapHeight); 

  int w_startx = (Nc::getTerminalWidth()  - Settings::mapWidth) / 2;
  int w_starty = (Nc::getTerminalHeight() - Settings::mapHeight) / 2;
  
  Nc::Window window{ Settings::mapWidth, Settings::mapHeight, w_startx, w_starty };
  window.setTitle("BOMBERMAN");

  int leftMenuStartX = (window.getPos().x - Settings::menuWidth - 3);
  Nc::Window leftMenu{ Settings::menuWidth, Settings::mapHeight, leftMenuStartX, w_starty };
  leftMenu.setTitle("PLAYER STATS");


  int rightMenuStartX = (window.getPos().x + window.getWidth() + 3);
  Nc::Window rightMenu{ Settings::menuWidth, Settings::mapHeight, rightMenuStartX, w_starty };
  rightMenu.setTitle("LEVEL STATS");
  

  constexpr int numLevels{ 2 };
  const char* paths[numLevels]{ "levels/level_01.txt", "levels/level_02.txt" };

  LevelList levelList{ paths, numLevels };
  Level* currLevel{ levelList.getLevel() };

  Player player{ 5, 3, 2 };

  bool running = true;

  while (running)
  {
    if (!currLevel)
    {
      Nc::stopWithError(0, "No more levels");
      continue; // non servirebbe ma per chiarezza
    }

    if (!player.isAlive())
    {
      Nc::stopWithError(0, "Game over");
      continue; // non servirebbe ma per chiarezza
    }

    Nc::Key key{ Nc::getKeyPressed() };
    Direction dir{ Direction::None };

    switch (key)
    {
      case Nc::Key::Escape: 
      case Nc::Key::Q: 
        running = false;
        break;

      case Nc::Key::Up:
      case Nc::Key::W:
        dir = Direction::Up;
        break;

      case Nc::Key::Down:
      case Nc::Key::S:
        dir = Direction::Down;
        break;

      case Nc::Key::Right:
      case Nc::Key::D:
        dir = Direction::Right;
        break;

      case Nc::Key::Left:
      case Nc::Key::A:
        dir = Direction::Left;
        break;

      case Nc::Key::E:
      case Nc::Key::Enter:
      {
        Bomb bomb = player.placeBomb();
        if (bomb.getStatus() != Bomb::Status::Finished)
          currLevel->addBomb(bomb);

        break;
      }
        
      default:
        dir = Direction::None;
        break;
    }

    window.clear();
    leftMenu.clear();
    rightMenu.clear();

    currLevel->movePlayer(player, dir);
    currLevel->moveEnemies();
    currLevel->handleBombs(player);
    currLevel->handleEnemies(player);
    player.handleItems();

    player.draw(window);
    currLevel->drawItems(window);
    currLevel->drawEnemies(window);
    currLevel->drawWalls(window);
    currLevel->drawBombs(window);
  
    
    leftMenu.write("Lives: ", 2, 5);
    for (int i = 0; i < player.getLives(); i++)
      leftMenu.write("♥ ", 9 + i*2, 5);

    leftMenu.write("Points: ", 2, 7);
    leftMenu.writeInt(player.getPoints(), 10, 7);

    rightMenu.write("Level: ", 2, 5);
    rightMenu.writeInt(currLevel->getLevelNumber(), 9, 5);

    window.display();
    leftMenu.display();
    rightMenu.display();

    if (currLevel->shouldGoNextLevel()) 
    {
      currLevel->pause();
      levelList.goNext();
      currLevel = levelList.getLevel();
      if (currLevel)
      {
        currLevel->start();
        Nc::Point pos = currLevel->getDoorPrevPos();
        player.setPos(pos.x + Settings::entityWidth, pos.y);
      }
    }

    if (currLevel->shouldGoPrevLevel()) 
    {
      currLevel->pause();
      levelList.goBack();
      currLevel = levelList.getLevel();
      if (currLevel)
      {
        currLevel->start();
        Nc::Point pos = currLevel->getDoorNextPos();
        player.setPos(pos.x - Settings::entityWidth, pos.y);
      }
    }
    
    Nc::sleepFor(10);
  }

  Nc::stop();
}