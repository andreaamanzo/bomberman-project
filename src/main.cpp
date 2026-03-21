#include "NcTypes.hpp"
#include "Player.hpp"
#include "NcWrapper.hpp"
#include "Direction.hpp"
#include "Settings.hpp"
#include "Level.hpp"

int main() 
{
  Nc::init();
  
  // la grandezza minima effettiva poi la decideremo
  Nc::checkTerminalSize(Settings::mapWidth * 1.3, Settings::mapHeight * 1.3); 

  int w_startx = (Nc::getTerminalWidth()  - Settings::mapWidth) / 2;
  int w_starty = (Nc::getTerminalHeight() - Settings::mapHeight) / 2;

  Nc::Window window{ Settings::mapWidth, Settings::mapHeight, w_startx, w_starty };
  window.setTitle("Bomberman");

  Level testLevel{ 0, "levels/level_01.txt" };

  Player player{ 5, 6, 4 };

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
      default:
        dir = Direction::None;
        break;
    }

    player.move(dir);

    window.clear();

    testLevel.drawWalls(window);

    player.draw(window);
    
    window.display();

    Nc::sleepFor(20);
  }

  Nc::stop();
}