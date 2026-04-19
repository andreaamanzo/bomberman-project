#include "Enemy.hpp"
#include "NcWrapper.hpp"
#include "Player.hpp"
#include "Direction.hpp"
#include "Settings.hpp"
#include "LevelList.hpp"
#include "Level.hpp"
#include "Bomb.hpp"
#include <stdio.h>
#include <iostream>

int main() 
{
  Nc::init();
  
  // grandezza minima
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
  
  constexpr int numLevels{ 3 };
  const char* paths[numLevels]{ "levels/level_01.txt", "levels/level_02.txt", "levels/level_03.txt" };

  LevelList levelList{ paths, numLevels };
  Level* currLevel{ levelList.getLevel() };
  currLevel->start();

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
      Nc::stopWithError(0, "Game over (lives finished)");
      continue; // non servirebbe ma per chiarezza
    }

    currLevel->updateTime();

    if (currLevel->checkTimeFinished())
    {
      Nc::stopWithError(0, "Game over (time finished)");
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

    leftMenu.write("Bomb Radius: ", 2, 9);
    leftMenu.writeInt(player.getBombRadius(), 15, 9);

    char str[64];
    sprintf(str, "Bombs: %d/%d", player.getMaxBombs() - player.getPlacedBombs(), player.getMaxBombs());
    leftMenu.write(str, 2, 11);

    rightMenu.write("Level: ", 2, 5);
    rightMenu.writeInt(currLevel->getLevelNumber(), 9, 5);

    char time[64];
    int secs = currLevel->getTimeLeftSec();
    if (secs % 60 >= 10)
      sprintf(time, "Time Left: %d:%d", secs/60, secs%60);
    else
      sprintf(time, "Time Left: %d:0%d", secs/60, secs%60);

    rightMenu.write(time, 2, 7);

    window.display();
    leftMenu.display();
    rightMenu.display();

    if (currLevel->isCompleted())
    {
      // punti per il completamento del livello
      player.addPoints(500 + currLevel->getTimeLeftSec() * 10); 

      player.restoreAllBombs();
      currLevel->removeAllBombs();

      levelList.removeCurrent();
      currLevel = levelList.getLevel();
      if (currLevel)
      {
        window.clear();
        window.write("LEVEL COMPLETED!", window.getWidth() / 2 - 8, window.getHeight() / 2, Nc::Color::Gold);
        window.display();
        Nc::sleepFor(1500);

        if (levelList.isCurrFirst())
          currLevel->removePrevDoor();
        
        if (levelList.isCurrLast())
          currLevel->removeNextDoor();
        
        currLevel->start();
        player.atRespown();
      }
      else
      {
        // win
      }
    }
    else if (currLevel->shouldGoNextLevel()) 
    {
      currLevel->pause();
      player.restoreAllBombs();
      currLevel->removeAllBombs();
      levelList.goNext();
      currLevel = levelList.getLevel();
      if (currLevel)
      {
        currLevel->start();
        Nc::Point pos = currLevel->getDoorPrevPos();
        player.setPos(pos.x + Settings::entityWidth, pos.y);
      }
    }
    else if (currLevel->shouldGoPrevLevel()) 
    {
      currLevel->pause();
      player.restoreAllBombs();
      currLevel->removeAllBombs();
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