#ifndef MENU_HPP
#define MENU_HPP

#include "NcWrapper.hpp"

class Menu
{
public:
  enum class Option
  {
    Game,
    Scoreboard,
    Close,
    Menu,
  };

  Menu();

  Option getMenuOption();

private:
  Nc::Window m_mainWindow;
};

#endif