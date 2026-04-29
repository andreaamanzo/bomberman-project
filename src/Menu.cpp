#include "Menu.hpp"
#include "Settings.hpp"

Menu::Menu() 
  : m_mainWindow{ Settings::mapWidth, Settings::mapHeight,
                 (Nc::getTerminalWidth()  - Settings::mapWidth) / 2, 
                 (Nc::getTerminalHeight() - Settings::mapHeight) / 2 }
{
  m_mainWindow.setTitle("BOMBERMAN MENU");
}

Menu::Option Menu::getMenuOption()
{
  // disegna tutto
  m_mainWindow.write("Start new game", (Settings::mapWidth - 14)/2, (Settings::mapHeight - 1)/2);
  m_mainWindow.write("Show scoreboard", (Settings::mapWidth - 15)/2, Settings::mapHeight/2);
  m_mainWindow.write("Quit", (Settings::mapWidth - 4)/2, (Settings::mapHeight + 1)/2);

  
  // display

  // prendi input
}