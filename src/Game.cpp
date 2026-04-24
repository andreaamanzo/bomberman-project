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
  , m_playerMenu{ Settings::menuWidth, Settings::mapHeight / 2 - 1, 
                 (m_mainWindow.getPos().x - Settings::menuWidth - 3), 
                  m_mainWindow.getPos().y }
  , m_itemsMenu{ Settings::menuWidth, Settings::mapHeight / 2 - 1, 
                (m_mainWindow.getPos().x - Settings::menuWidth - 3), 
                 m_mainWindow.getPos().y + m_mainWindow.getHeight() / 2 + 1 }
  , m_levelMenu{ Settings::menuWidth, Settings::mapHeight / 2 - 1, 
                (m_mainWindow.getPos().x + m_mainWindow.getWidth() + 3),
                 m_mainWindow.getPos().y }
  , m_controlsMenu{ Settings::menuWidth, Settings::mapHeight / 2 - 1, 
                   (m_mainWindow.getPos().x + m_mainWindow.getWidth() + 3),
                    m_mainWindow.getPos().y + m_mainWindow.getHeight() / 2 + 1 }
  , m_player{ 3, Settings::entityWidth, Settings::entityHeight }
{
  m_mainWindow.setTitle("BOMBERMAN");
  m_playerMenu.setTitle("PLAYER STATS");
  m_itemsMenu.setTitle("ITEMS INFO");
  m_levelMenu.setTitle("LEVEL STATS");
  m_controlsMenu.setTitle("CONTROLS");
}

void Game::drawMessage(const char* message, const char* subMessage)
{
  m_mainWindow.clear();

  m_mainWindow.write(message, 
                     m_mainWindow.getWidth() / 2 - static_cast<int>(strlen(message)) / 2, 
                     m_mainWindow.getHeight() / 2 - 1, 
                     Nc::Color::Gold);
  m_mainWindow.write(subMessage, 
                     m_mainWindow.getWidth() / 2 - static_cast<int>(strlen(subMessage)) / 2, 
                     m_mainWindow.getHeight() / 2 + 1, 
                     Nc::Color::Gold);

  char msg[]{ "Press any key to continue..." };
  m_mainWindow.write(msg, 
                     m_mainWindow.getWidth() / 2 - static_cast<int>(strlen(msg)) / 2, 
                     m_mainWindow.getHeight() - 2, 
                     Nc::Color::Gold);

  m_mainWindow.display();

  Nc::sleepFor(1500); 
  Nc::waitForKeyPressd();
}

bool Game::checkLoseConditions()
{
  if (!m_currLevel)
    Nc::stopWithError(1, "Current level not found");

  if (!m_player.isAlive())
  {
    drawMessage("GAME OVER!", "You're out of lives");
    return false;
  }

  if (m_currLevel->checkTimeFinished())
  {
    drawMessage("GAME OVER!", "Time's up");
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

void Game::writeOnMenus()
{
  // ===== PLAYER MENU =====
  m_playerMenu.write("Lives: ", 2, 3);
  int lives = m_player.getLives();

  for (int i = 0; i < lives; i++)
    m_playerMenu.write("♥ ", 9 + i * 2, 3, Nc::Color::Red);

  if (lives == m_player.getMaxLives())
    m_playerMenu.write(" max", 9 + lives * 2, 3, Nc::Color::Red);

  m_playerMenu.write("Points: ", 2, 6);
  m_playerMenu.writeInt(m_player.getPoints(), 10, 6, Nc::Color::Yellow);

  m_playerMenu.write("Bombs: ", 2, 9);

  int maxBombs = m_player.getCurrMaxBombs();
  int availableBombs = maxBombs - m_player.getPlacedBombs();

  for (int i = 0; i < availableBombs; i++)
  {
    m_playerMenu.write(" ╽ ", 9 + i * 2, 8, Nc::Color::Orange);
    m_playerMenu.write("(●)", 9 + i * 2, 9, Nc::Color::Orange);
  }

  for (int i = availableBombs; i < maxBombs; i++)
  {
    m_playerMenu.write(" ╽ ", 9 + i * 2, 8, Nc::Color::White);
    m_playerMenu.write("(●)", 9 + i * 2, 9, Nc::Color::White);
  }

  if (maxBombs == m_player.getMaxBombs())
    m_playerMenu.write(" max", 10 + maxBombs * 2, 9, Nc::Color::Orange);

  m_playerMenu.write("Bomb Radius: ", 2, 12);
  m_playerMenu.writeInt(m_player.getBombRadius(), 15, 12);

  // ===== ITEMS MENU =====
  m_itemsMenu.write("|+|", 2, 3, Nc::Color::Yellow);
  m_itemsMenu.write("|+|", 2, 4, Nc::Color::Yellow);
  m_itemsMenu.write("+1 Bomb", 6, 3);

  m_itemsMenu.write("|↑|", 2, 6, Nc::Color::Yellow);
  m_itemsMenu.write("|↓|", 2, 7, Nc::Color::Yellow);
  m_itemsMenu.write("+1 Bomb Radius", 6, 6);

  m_itemsMenu.write("|❤|", 2, 9, Nc::Color::Yellow);
  m_itemsMenu.write("|❤|", 2, 10, Nc::Color::Yellow);
  m_itemsMenu.write("+1 Life", 6, 9);

  m_itemsMenu.write("|⛨|", 2, 12, Nc::Color::Yellow);
  m_itemsMenu.write("|⛨|", 2, 13, Nc::Color::Yellow);
  m_itemsMenu.write("Shield (10 sec)", 6, 12);

  m_itemsMenu.write("|☀|", 2, 15, Nc::Color::Yellow);
  m_itemsMenu.write("|☀|", 2, 16, Nc::Color::Yellow);
  m_itemsMenu.write("Power (10 sec)", 6, 15);

  // ===== LEVEL MENU =====
  m_levelMenu.write("Level: ", 2, 3);
  m_levelMenu.writeInt(m_currLevel->getLevelNumber(), 9, 3);

  m_levelMenu.write("Enemies: ", 2, 6);
  m_levelMenu.writeInt(m_currLevel->getEnemiesNumber(), 11, 6);

  char timeStr[64];
  int secs = m_currLevel->getTimeLeftSec();

  snprintf(
    timeStr,
    sizeof(timeStr),
    "Time Left: %d:%02d",
    secs / 60,
    secs % 60
  );

  m_levelMenu.write(timeStr, 2, 9);

  // ===== CONTROLS MENU =====
  m_controlsMenu.write("Move Up:     W / ↑",      2, 3);
  m_controlsMenu.write("Move Down:   S / ↓",      2, 4);
  m_controlsMenu.write("Move Left:   A / ←",      2, 5);
  m_controlsMenu.write("Move Right:  D / →",      2, 6);

  m_controlsMenu.write("Place Bomb:  E / Enter",  2, 8);
  m_controlsMenu.write("Quit:        Q / Esc",    2, 10);
}

void Game::render()
{
  // cancella tutto
  m_mainWindow.clear();
  m_playerMenu.clear();
  m_itemsMenu.clear();
  m_levelMenu.clear();
  m_controlsMenu.clear();
  
  // disegna i vari elementi della mappa da gioco
  m_player.draw(m_mainWindow);
  m_currLevel->drawItems(m_mainWindow);
  m_currLevel->drawEnemies(m_mainWindow);
  m_currLevel->drawWalls(m_mainWindow);
  m_currLevel->drawBombs(m_mainWindow);

  // dsegna le scritte sui menu laterali
  writeOnMenus();

  // display finale
  m_mainWindow.display();
  m_playerMenu.display();
  m_itemsMenu.display();
  m_levelMenu.display();
  m_controlsMenu.display();
}
 
void Game::handleCompletedLevel()
{
  int bonus = 500 + m_currLevel->getTimeLeftSec() * 10;
  m_player.addPoints(bonus);

  leaveCurrentLevel();

  m_levelList.removeCurrent();

  if (!initCurrentLevel())
  {
    drawMessage("YOU WON!", "Congratulations!");
    m_running = false;
    return;
  }

  drawMessage("LEVEL COMPLETED!");

  if (m_levelList.isCurrFirst())
    m_currLevel->removePrevDoor();

  if (m_levelList.isCurrLast())
    m_currLevel->removeNextDoor();
    
  m_player.atRespown();
}

void Game::leaveCurrentLevel()
{
  m_player.restoreAllBombs();
  m_currLevel->removeAllBombs();
  m_currLevel->pause();
}

bool Game::initCurrentLevel()
{
  m_currLevel = m_levelList.getLevel();

  if (!m_currLevel)
    return false;
    
  Nc::Point prevDoorPos = m_currLevel->getDoorPrevPos();
  m_player.setRespownPoint(prevDoorPos.x + Settings::entityWidth, prevDoorPos.y);

  m_currLevel->start();

  return true;
}

void Game::goToNextLevel()
{
  leaveCurrentLevel();

  m_levelList.goNext();
  
  if (!initCurrentLevel())
    return;

  Nc::Point pos = m_currLevel->getDoorPrevPos();
  m_player.setPos(pos.x + Settings::entityWidth, pos.y);
}

void Game::goToPreviousLevel()
{
  leaveCurrentLevel();

  m_levelList.goBack();

  if (!initCurrentLevel())
    return;

  Nc::Point pos = m_currLevel->getDoorNextPos();
  m_player.setPos(pos.x - Settings::entityWidth, pos.y);
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

  // cancella le window del gioco
  Nc::clearAll();
  
  return m_player.getPoints();
}
