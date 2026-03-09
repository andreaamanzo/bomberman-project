#include "NcFunctions.hpp"
#include "NcTypes.hpp"
#include "NcWrapper.hpp"
#include <chrono>

int main() 
{
  Nc::init();

  int w_width = Nc::getScreenWidth()/2;
  int w_height = Nc::getScreenHeight()/2;
  int w_startx = (Nc::getScreenWidth() - w_width) / 2;
  int w_starty = (Nc::getScreenHeight() - w_height) / 2;

  Nc::Window window{ w_width, w_height, w_startx, w_starty };
  window.setTitle("Bomberman");

  bool running = true;
  while (running)
  {
    Nc::Key key = Nc::getKeyPressed();
    if (key == Nc::Key::Escape) running = false;
    window.clear();
    window.display();
    Nc::sleepFor(std::chrono::milliseconds{ 20 });
  }

  Nc::stop();
}