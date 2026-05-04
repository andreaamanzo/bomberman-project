#include "Menu.hpp"
#include "NcFunctions.hpp"
#include "NcTypes.hpp"
#include "Settings.hpp"
#include <cstring>

Menu::Menu() 
  : m_mainWindow{ Settings::mapWidth, Settings::mapHeight,
                 (Nc::getTerminalWidth()  - Settings::mapWidth) / 2, 
                 (Nc::getTerminalHeight() - Settings::mapHeight) / 2 }
{
  m_mainWindow.setTitle("BOMBERMAN MENU");
}

Menu::Option Menu::getMenuOption()
{
  int highlight = 0;
  Nc::Key key;
  
  
  const char* stringArr[3]{"Start new game","Show scoreboard","Quit"};

  while (true)
  {
    m_mainWindow.clear();
    for (int i = 0; i < 3; i++)
    {
      int posX = (Settings::mapWidth - static_cast<int>(strlen(stringArr[i])))/2;
      int posY = (Settings::mapHeight - 2 + i*2)/2;

      if (i == highlight)
        m_mainWindow.write(stringArr[i], posX, posY, Nc::Color::Black, Nc::Color::White);
      else 
        m_mainWindow.write(stringArr[i], posX, posY);

    }
    key = Nc::getKeyPressed();

    switch (key)
    {
    case Nc::Key::Down:
      highlight++;
      if (highlight > 2) highlight = 0;
      break;
    case Nc::Key::Up:
      highlight--;
      if (highlight < 0) highlight = 2;
      break;
    case Nc::Key::Enter:
      return static_cast<Option>(highlight);
    case Nc::Key::Q:
    case Nc::Key::Escape:
      return Option::Close;
    default:
      break;
    }
    
    m_mainWindow.display();
    Nc::sleepFor(20);
  }
  
}