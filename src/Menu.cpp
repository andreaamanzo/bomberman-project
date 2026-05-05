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
  Enemy enemy{ Enemy::Type::Second_Enemy, 15, 10 };
  enemy.setDelaySpeed(60);
  Player player{ 1, 10, 30 };
  player.setDelaySpeed(30);

  Direction playerDir{ Direction::Right };

  int highlight = 0;
  Nc::Key key;
  
  const char* stringArr[3]{
    "[      New game       ]",
    "[   Show scoreboard   ]",
    "[        Quit         ]"
  };

  while (true)
  {
    m_mainWindow.clear();

    enemy.draw(m_mainWindow);
    player.draw(m_mainWindow);

    for (int i = 0; i < 3; i++)
    {
      int posX = (Settings::mapWidth - static_cast<int>(strlen(stringArr[i])))/2;
      int posY = (Settings::mapHeight - 6 + i*4)/2;

      if (i == highlight)
        m_mainWindow.write(stringArr[i], posX, posY, Nc::Color::Black, Nc::Color::Gold);
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

    if (enemy.shouldMove()) enemy.move();
    if (player.shouldMove()) player.move(playerDir);

    if ((enemy.getX() <= 0) ||
        (enemy.getX() >= m_mainWindow.getWidth() - Settings::entityWidth) ||
        (enemy.getY() <= 0) ||
        (enemy.getY() >= m_mainWindow.getHeight() - Settings::entityHeight))
    {
      enemy.setDirection(getOppositeDir(enemy.getDirection()));
      enemy.move();
    }

    if ((player.getX() <= 0) ||
        (player.getX() >= m_mainWindow.getWidth() - Settings::entityWidth) ||
        (player.getY() <= 0) ||
        (player.getY() >= m_mainWindow.getHeight() - Settings::entityHeight))
    {
      playerDir = getOppositeDir(playerDir);
      player.move(playerDir);
    }


    if (Random::get(1, 100) == 1)
    {
      enemy.setDirection(static_cast<Direction>(Random::get(1, 4)));
    }

    if (Random::get(1, 100) == 1)
    {
      playerDir = static_cast<Direction>(Random::get(1, 4));
    }

    m_mainWindow.display();
    Nc::sleepFor(10);
  }
  
}