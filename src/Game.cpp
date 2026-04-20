#include "Game.hpp"
#include "NcWrapper.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Direction.hpp"
#include "Settings.hpp"
#include "LevelList.hpp"
#include "Level.hpp"
#include "Bomb.hpp"
#include "ScoreList.hpp"
#include <cstring>

Game::Game(int numLevels, const char* levelPaths[])
  : m_levelList{ levelPaths, numLevels }
  , m_currLevel{ m_levelList.getLevel() }
  , m_mainWindow{ Settings::mapWidth, Settings::mapHeight, 
                  (Nc::getTerminalWidth()  - Settings::mapWidth) / 2, 
                  (Nc::getTerminalHeight() - Settings::mapHeight) / 2 }
  , m_leftMenu{ Settings::menuWidth, Settings::mapHeight, 
                (m_mainWindow.getPos().x - Settings::menuWidth - 3), 
                 m_mainWindow.getPos().y }
  , m_rightMenu{ Settings::menuWidth, Settings::mapHeight, 
                (m_mainWindow.getPos().x + m_mainWindow.getWidth() + 3),
                 m_mainWindow.getPos().y }
  , m_player{ 5, Settings::entityWidth, Settings::entityHeight }
{
  m_mainWindow.setTitle("BOMBERMAN");
  m_leftMenu.setTitle("PLAYER STATS");
  m_rightMenu.setTitle("LEVEL STATS");
}

void Game::drawMessage(int displayTime, const char* message, const char* subMessage)
{
  m_mainWindow.clear();

  m_mainWindow.write(message, 
                     m_mainWindow.getWidth() / 2 - static_cast<int>(strlen(message)) / 2, 
                     m_mainWindow.getHeight() / 2, 
                     Nc::Color::Gold);
  m_mainWindow.write(subMessage, 
                     m_mainWindow.getWidth() / 2 - static_cast<int>(strlen(subMessage)) / 2, 
                     m_mainWindow.getHeight() / 2 + 2, 
                     Nc::Color::Gold);

  m_mainWindow.display();

  Nc::sleepFor(displayTime);
}

bool Game::checkLoseConditions()
{
  if (!m_currLevel)
    Nc::stopWithError(1, "Current level not found");

  if (!m_player.isAlive())
  {
    drawMessage(2000, "GAME OVER!", "You're out of lives");
    return false;
  }

  if (m_currLevel->checkTimeFinished())
  {
    drawMessage(2000, "GAME OVER!", "Time's up");
    return false;
  }

  return true;
}

void Game::update()
{
  Nc::Key key{ Nc::getKeyPressed() };
  Direction dir{ Direction::None };

  switch (key)
  {
    case Nc::Key::Escape: 
    case Nc::Key::Q: 
      m_running = false;
      break;

    case Nc::Key::Up:
    case Nc::Key::W:
      dir = Direction::Up;
      break;

    case Nc::Key::Down:
    case Nc::Key::S:
      dir = Direction::Down;
      break;

    case Nc::Key::Right:
    case Nc::Key::D:
      dir = Direction::Right;
      break;

    case Nc::Key::Left:
    case Nc::Key::A:
      dir = Direction::Left;
      break;

    case Nc::Key::E:
    case Nc::Key::Enter:
    {
      Bomb bomb = m_player.placeBomb();
      if (bomb.getStatus() != Bomb::Status::Finished)
        m_currLevel->addBomb(bomb);

      break;
    }
      
    default:
      dir = Direction::None;
      break;
  }

  m_currLevel->movePlayer(m_player, dir);
  m_currLevel->moveEnemies();

  m_currLevel->handleBombs(m_player);
  m_currLevel->handleEnemies(m_player);
  m_player.handleItems();

  m_currLevel->updateTime();
}

void Game::render()
{
  // cancella tutto
  m_mainWindow.clear();
  m_leftMenu.clear();
  m_rightMenu.clear();
  
  // disegna i vari elementi della mappa da gioco
  m_player.draw(m_mainWindow);
  m_currLevel->drawItems(m_mainWindow);
  m_currLevel->drawEnemies(m_mainWindow);
  m_currLevel->drawWalls(m_mainWindow);
  m_currLevel->drawBombs(m_mainWindow);

  // dsegna le scritte sui menu laterali
  m_leftMenu.write("Lives: ", 2, 5);
  for (int i = 0; i < m_player.getLives(); i++)
    m_leftMenu.write("♥ ", 9 + i*2, 5);

  m_leftMenu.write("Points: ", 2, 7);
  m_leftMenu.writeInt(m_player.getPoints(), 10, 7);

  m_leftMenu.write("Bomb Radius: ", 2, 9);
  m_leftMenu.writeInt(m_player.getBombRadius(), 15, 9);

  char str[64];
  snprintf(str, sizeof(str), "Bombs: %d/%d", m_player.getMaxBombs() - m_player.getPlacedBombs(), m_player.getMaxBombs());
  m_leftMenu.write(str, 2, 11);

  m_rightMenu.write("Level: ", 2, 5);
  m_rightMenu.writeInt(m_currLevel->getLevelNumber(), 9, 5);

  char time[64];
  int secs = m_currLevel->getTimeLeftSec();
  snprintf(time, sizeof(time), "Time Left: %d:%02d", secs/60, secs%60);

  m_rightMenu.write(time, 2, 7);

  // display finale
  m_mainWindow.display();
  m_leftMenu.display();
  m_rightMenu.display();
}
 
void Game::handleCompletedLevel()
{
  int bonus = 500 + m_currLevel->getTimeLeftSec() * 10;
  m_player.addPoints(bonus);

  leaveCurrentLevel();

  m_levelList.removeCurrent();
  m_currLevel = m_levelList.getLevel();

  if (!m_currLevel)
  {
    drawMessage(2000, "YOU WON!", "Congratulations!");
    m_running = false;
    return;
  }

  drawMessage(1500, "LEVEL COMPLETED!");

  if (m_levelList.isCurrFirst())
    m_currLevel->removePrevDoor();

  if (m_levelList.isCurrLast())
    m_currLevel->removeNextDoor();

  m_currLevel->start();
  m_player.atRespown();
}

void Game::goToNextLevel()
{
  leaveCurrentLevel();

  m_levelList.goNext();
  m_currLevel = m_levelList.getLevel();

  if (!m_currLevel)
    return;

  m_currLevel->start();

  Nc::Point pos = m_currLevel->getDoorPrevPos();
  m_player.setPos(pos.x + Settings::entityWidth, pos.y);
}

void Game::goToPreviousLevel()
{
  leaveCurrentLevel();

  m_levelList.goBack();
  m_currLevel = m_levelList.getLevel();

  if (!m_currLevel)
    return;

  m_currLevel->start();

  Nc::Point pos = m_currLevel->getDoorNextPos();
  m_player.setPos(pos.x - Settings::entityWidth, pos.y);
}

void Game::leaveCurrentLevel()
{
  m_player.restoreAllBombs();
  m_currLevel->removeAllBombs();
  m_currLevel->pause();
}

int Game::play()
{
  m_currLevel->start();

  while (m_running)
  {
    if (!checkLoseConditions())
    {
      m_running = false;
      break;
    }

    update();

    render();

    if (m_currLevel->isCompleted())
      handleCompletedLevel();
    else if (m_currLevel->shouldGoNextLevel()) 
      goToNextLevel();
    else if (m_currLevel->shouldGoPrevLevel()) 
      goToPreviousLevel();
    
    Nc::sleepFor(10);
  }

  return m_player.getPoints();
}
