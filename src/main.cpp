#include "NcWrapper.hpp"
#include <chrono>

int main() 
{
  Nc::init();
  Nc::Window window{ 20, 10 };
  window.setTitle("Bomberman");

  while (true)
  {
    window.clear();
    window.display();
  
    Nc::sleepFor(std::chrono::milliseconds{ 20 });
  }
}