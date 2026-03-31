#include "NcTypes.hpp"
#include "Player.hpp"
#include "NcWrapper.hpp"
#include "Direction.hpp"
#include "Settings.hpp"
#include "LevelList.hpp"
#include "Level.hpp"
#include "Bomb.hpp"
#include "Enemy.hpp"

#include <iostream>

int main() 
{
  Nc::init();
  
  // la grandezza minima effettiva poi la decideremo
  Nc::checkTerminalSize(Settings::mapWidth * 1.3, Settings::mapHeight * 1.3); 

  int w_startx = (Nc::getTerminalWidth()  - Settings::mapWidth) / 2;
  int w_starty = (Nc::getTerminalHeight() - Settings::mapHeight) / 2;

  Nc::Window window{ Settings::mapWidth, Settings::mapHeight, w_startx, w_starty };
  window.setTitle("BOMBERMAN");

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

    Nc::Key key{ Nc::getKeyPressed() };
    Direction dir;

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

    currLevel->movePlayer(player, dir);
    currLevel->handleBombs(player);

    currLevel->drawWalls(window);
    player.draw(window);
    currLevel->drawBombs(window);
    
    window.display();

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

    Nc::sleepFor(20);
  }

  Nc::stop();
}