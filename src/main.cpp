#include "NcFunctions.hpp"
#include "NcTypes.hpp"
#include "NcWrapper.hpp"
#include "Direction.hpp"

int main() 
{
  Nc::init();

  int w_width  = Nc::getTerminalWidth() / 2;
  int w_height = Nc::getTerminalHeight() / 2;
  int w_startx = (Nc::getTerminalWidth() - w_width) / 2;
  int w_starty = (Nc::getTerminalHeight() - w_height) / 2;

  Nc::Window window{ w_width, w_height, w_startx, w_starty };
  window.setTitle("Bomberman");

  Nc::Sprite2x3 spriteExample{ L"ʘ‿ʘ", L"╰╩╯", Nc::Color::Green };

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
        dir = Direction::Up;
      default:
        break;
    }

    // player.move(dir);

    // level.addBomb(player.placeBomb());

    // level.d

    window.clear();
    window.draw(spriteExample, 10, 10);
    window.display();

    Nc::sleepFor(20);
  }

  Nc::stop();
}