#ifndef MENU_HPP
#define MENU_HPP

#include "NcWrapper.hpp"

class Menu
{
public:
  enum class Option
  {
    Menu,
    Scoreboard,
    Game,
    Close,
  };

  Menu();

  Option getMenuOption();

private:
  Nc::Window m_mainWindow;
  bool m_running{ true };

};

#endif