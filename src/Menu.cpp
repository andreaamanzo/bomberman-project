#include "Menu.hpp"
#include "NcFunctions.hpp"
#include "NcTypes.hpp"
#include "Settings.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Random.hpp"
#include "Direction.hpp"
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
  
  constexpr int menuItems = 3;
  const int spacing = 2;
  const int menuHeight = (menuItems - 1) * spacing;
  const char* stringArr[menuItems]{
    "[      New game       ]",
    "[   Show scoreboard   ]",
    "[        Quit         ]"
  };

  constexpr int titleLines = 6;
  const int titleLineLen = 81;
  const char* title[titleLines] =
  {
    "██████╗  ██████╗ ███╗   ███╗██████╗ ███████╗██████╗ ███╗   ███╗ █████╗ ███╗   ██╗",
    "██╔══██╗██╔═══██╗████╗ ████║██╔══██╗██╔════╝██╔══██╗████╗ ████║██╔══██╗████╗  ██║",
    "██████╔╝██║   ██║██╔████╔██║██████╔╝█████╗  ██████╔╝██╔████╔██║███████║██╔██╗ ██║",
    "██╔══██╗██║   ██║██║╚██╔╝██║██╔══██╗██╔══╝  ██╔══██╗██║╚██╔╝██║██╔══██║██║╚██╗██║",
    "██████╔╝╚██████╔╝██║ ╚═╝ ██║██████╔╝███████╗██║  ██║██║ ╚═╝ ██║██║  ██║██║ ╚████║",
    "╚═════╝  ╚═════╝ ╚═╝     ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝"
  };

  constexpr int authorsCount = 3;
  const char* authors[authorsCount] =
  {
    "Andrea Manzo",
    "Tommaso Lissandrin",
    "Alessandro Godani"
  };

  while (true)
  {
    m_mainWindow.clear();

    for (int i = 0; i < titleLines; i++)
    {
      int posX = (Settings::mapWidth - titleLineLen) / 2;
      int posY = 3 + i;

      m_mainWindow.write(title[i], posX, posY, Nc::Color::Gold);
    }

    for (int i = 0; i < 3; i++)
    {
      int posX = (Settings::mapWidth - static_cast<int>(strlen(stringArr[i])))/2;
      int posY = (Settings::mapHeight - menuHeight) / 2 + i * spacing;

      if (i == highlight)
        m_mainWindow.write(stringArr[i], posX, posY, Nc::Color::Black, Nc::Color::Gold);
      else 
        m_mainWindow.write(stringArr[i], posX, posY);
    }

    for (int i = 0; i < authorsCount; i++)
    {
      int len = static_cast<int>(strlen(authors[i]));

      int posX = (Settings::mapWidth - len) / 2;
      int posY = Settings::mapHeight - 5 + i;

      m_mainWindow.write(authors[i], posX, posY, Nc::Color::LightGray);
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
    Nc::sleepFor(10);
  }
  
}