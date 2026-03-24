#include "NcTypes.hpp"
#include "Player.hpp"
#include "NcWrapper.hpp"
#include "Direction.hpp"
#include "Settings.hpp"
#include "Level.hpp"
#include "Bomb.hpp"

int main() 
{
  Nc::init();
  
  // la grandezza minima effettiva poi la decideremo
  Nc::checkTerminalSize(Settings::mapWidth * 1.3, Settings::mapHeight * 1.3); 

  int w_startx = (Nc::getTerminalWidth()  - Settings::mapWidth) / 2;
  int w_starty = (Nc::getTerminalHeight() - Settings::mapHeight) / 2;

  Nc::Window window{ Settings::mapWidth, Settings::mapHeight, w_startx, w_starty };
  window.setTitle("BOMBERMAN");

  Level testLevel{ 0, "levels/level_01.txt" };

  Player player{ 5, 3, 2 };

  Bomb* testBomb{ nullptr };

  bool running = true;

  while (running)
  {
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

      case Nc::Key::X:
        delete testBomb;
        testBomb = player.placeBomb();
        break;
        
      default:
        dir = Direction::None;
        break;
    }

    player.move(dir);

    window.clear();

    testLevel.drawWalls(window);

    player.draw(window);

    if (testBomb)
      testBomb->draw(window);

    // per poter piazzare di nuvo la bomba: solo test
    player.restoreBomb();
    
    window.display();

    Nc::sleepFor(20);
  }

  Nc::stop();
}