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
  if (!m_player.hasIce())
  {
    m_currLevel->moveEnemies();
  }
  
  m_currLevel->handleBombs(m_player);
  m_currLevel->handleEnemies(m_player);
  m_player.handleItems();

  m_currLevel->updateTime();
}

void Game::writeTimedItems()
{
  const int START = 2;
  const int SPACING = 3;

  int n = m_player.getItemsListSize();
  const Item* items = m_player.getItemsList();

  int offset = 0;

  for (int i = 0; i < n; i++)
  {
    const Item& item = items[i];
    if (item.isTimed())
    {
      char itemStr[16];
      if (item.getType() == Item::Type::Ice)
        strcpy(itemStr, "Freeze");
      else if (item.getType() == Item::Type::Invulnerability)
        strcpy(itemStr, "Shield");

      char timeStr[24];
      int secs = item.getTimeLeftSec() + 1;
      if (secs > 20) secs = 20;
      for (int j = 0; j < secs; j++) timeStr[j] = '+';
      timeStr[secs] = '\0';

      char str[64];
      snprintf(str, sizeof(str), "%s time: %s", itemStr, timeStr);

      int y = START + SPACING * (4 + offset); // 4 = riga base dopo le info player
      m_playerMenu.write(str, START, y);

      offset++;
    }
  }
}

void Game::writeOnMenus()
{
  const int START = 2;
  const int SPACING = 3;
  const int SMALL_SPACING = 2;

  // ===== PLAYER MENU =====
  int row = 0;

  m_playerMenu.write("Lives: ", START, START + SPACING * row);
  int lives = m_player.getLives();

  for (int i = 0; i < lives; i++)
    m_playerMenu.write("♥ ", START + 7 + i * 2, START + SPACING * row, Nc::Color::Red);

  if (lives == m_player.getMaxLives())
    m_playerMenu.write(" max", START + 7 + lives * 2, START + SPACING * row, Nc::Color::Red);

  row++;

  m_playerMenu.write("Points: ", START, START + SPACING * row);
  m_playerMenu.writeInt(m_player.getPoints(), START + 8, START + SPACING * row, Nc::Color::Yellow);

  row++;

  m_playerMenu.write("Bombs: ", START, START + SPACING * row);

  int maxBombs = m_player.getCurrMaxBombs();
  int availableBombs = maxBombs - m_player.getPlacedBombs();

  for (int i = 0; i < maxBombs; i++)
  {
    int x = START + 7 + i * 2;
    int yBase = START + SPACING * row;

    Nc::Color color = (i < availableBombs) ? Nc::Color::Orange : Nc::Color::White;

    m_playerMenu.write(" ╽ ", x, yBase - 1, color);
    m_playerMenu.write("(●)", x, yBase, color);
  }

  if (maxBombs == m_player.getMaxBombs())
    m_playerMenu.write(" max", START + 8 + maxBombs * 2, START + SPACING * row, Nc::Color::Orange);

  row++;

  m_playerMenu.write("Bomb Radius: ", START, START + SPACING * row);
  m_playerMenu.writeInt(m_player.getBombRadius(), START + 13, START + SPACING * row);

  // timed items partono dopo le righe base
  writeTimedItems();

  // ===== ITEMS MENU =====
  row = 0;

  m_itemsMenu.write("|+|", START, START + SPACING * row, Nc::Color::Yellow);
  m_itemsMenu.write("|+|", START, START + SPACING * row + 1, Nc::Color::Yellow);
  m_itemsMenu.write("+1 Bomb", START + 4, START + SPACING * row);

  row++;

  m_itemsMenu.write("|↑|", START, START + SPACING * row, Nc::Color::Yellow);
  m_itemsMenu.write("|↓|", START, START + SPACING * row + 1, Nc::Color::Yellow);
  m_itemsMenu.write("+1 Bomb Radius", START + 4, START + SPACING * row);

  row++;

  m_itemsMenu.write("|❤|", START, START + SPACING * row, Nc::Color::Yellow);
  m_itemsMenu.write("|❤|", START, START + SPACING * row + 1, Nc::Color::Yellow);
  m_itemsMenu.write("+1 Life", START + 4, START + SPACING * row);

  row++;

  m_itemsMenu.write("|⛨|", START, START + SPACING * row, Nc::Color::Yellow);
  m_itemsMenu.write("|⛨|", START, START + SPACING * row + 1, Nc::Color::Yellow);
  m_itemsMenu.write("Shield (10 sec)", START + 4, START + SPACING * row);

  row++;

  m_itemsMenu.write("|❅|", START, START + SPACING * row, Nc::Color::Yellow);
  m_itemsMenu.write("|❅|", START, START + SPACING * row + 1, Nc::Color::Yellow);
  m_itemsMenu.write("Freeze enemies (10 sec)", START + 4, START + SPACING * row);

  // ===== LEVEL MENU =====
  row = 0;

  m_levelMenu.write("Level: ", START, START + SPACING * row);
  m_levelMenu.writeInt(m_currLevel->getLevelNumber(), START + 7, START + SPACING * row);

  row++;

  m_levelMenu.write("Enemies: ", START, START + SPACING * row);
  m_levelMenu.writeInt(m_currLevel->getEnemiesNumber(), START + 9, START + SPACING * row);

  row++;

  m_levelMenu.write("Items: ", START, START + SPACING * row);
  m_levelMenu.writeInt(m_currLevel->getItemsNumber(), START + 7, START + SPACING * row);

  row++;

  char timeStr[64];
  int secs = m_currLevel->getTimeLeftSec();

  snprintf(timeStr, sizeof(timeStr), "Time Left: %d:%02d", secs / 60, secs % 60);
  m_levelMenu.write(timeStr, START, START + SPACING * row);

  // ===== CONTROLS MENU =====
  row = 0;

  m_controlsMenu.write("Move Up:     W / ↑", START, START + SMALL_SPACING * row++);
  m_controlsMenu.write("Move Down:   S / ↓", START, START + SMALL_SPACING * row++);
  m_controlsMenu.write("Move Left:   A / ←", START, START + SMALL_SPACING * row++);
  m_controlsMenu.write("Move Right:  D / →", START, START + SMALL_SPACING * row++);

  m_controlsMenu.write("Place Bomb:  E / Enter", START, START + SPACING * row++);
  m_controlsMenu.write("Quit:        Q / Esc", START, START + SPACING * row);
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
