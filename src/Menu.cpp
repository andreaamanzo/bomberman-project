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
  int highlight{ 0 };
  
  const int spacing{ 2 };
  const int menuHeight{ (s_menuSize - 1) * spacing };

  while (true)
  {
    m_mainWindow.clear();

    // TITLE
    for (int i = 0; i < s_titleLines; i++)
    {
      int posX = (Settings::mapWidth - s_titleLineLen) / 2;
      int posY = 3 + i;

      m_mainWindow.write(s_title[i], posX, posY, Nc::Color::Gold);
    }

    // MENU OPTIONS
    for (int i = 0; i < 3; i++)
    {
      int posX = (Settings::mapWidth - static_cast<int>(strlen(s_menuOptions[i])))/2;
      int posY = (Settings::mapHeight - menuHeight) / 2 + i * spacing;

      if (i == highlight)
        m_mainWindow.write(s_menuOptions[i], posX, posY, Nc::Color::Black, Nc::Color::Gold);
      else 
        m_mainWindow.write(s_menuOptions[i], posX, posY);
    }

    // AUTHORS
    for (int i = 0; i < s_authorsSize; i++)
    {
      int len = static_cast<int>(strlen(s_authors[i]));

      int posX = (Settings::mapWidth - len) / 2;
      int posY = Settings::mapHeight - 5 + i;

      m_mainWindow.write(s_authors[i], posX, posY, Nc::Color::LightGray);
    }

    Nc::Key key = Nc::getKeyPressed();

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
    Nc::sleepFor(10);
  }
  
}