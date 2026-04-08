#include "Level.hpp"
#include "Bomb.hpp"
#include "Direction.hpp"
#include "Enemy.hpp"
#include "NcWrapper.hpp"
#include "Player.hpp"
#include "Random.hpp"
#include "Settings.hpp"
#include <fstream>
#include <iostream>

// ALE: utilizzata ai per imparare utilizzo ifstram e capire utilizzo generale
// delle librerie
Level::Level(int levelNumber, const char *mapFilePath)
    : m_levelNumber{levelNumber} {
  // leggo il file con ifstram
  std::ifstream file{mapFilePath};

  // controllo se il file è stato aperto correttamente, sennò exit
  if (!file.is_open())
    Nc::stopWithError(1, "Level loading failed: map file not found.");

  // parsing del file e inizializzazione mappa
  char c;
  int nrow = 0;
  int nchar = 0;

  while (file.get(c)) {
    if (nrow >= Settings::mapRows || nchar > Settings::mapCols)
      Nc::stopWithError(1, "Invalid map: exceeds maximum allowed size.");

    if (c == '\n') {
      if (nchar < Settings::mapCols)
        Nc::stopWithError(1, "Invalid map: incorrect number of columns.");

      nrow++;
      nchar = 0;
    } else {
      switch (c) {
      case 'X':
        m_map[nrow][nchar] = Tile::Wall;
        break;
      case '#':
        m_map[nrow][nchar] = Tile::BreakableWall;
        break;
      case 'O':
        m_map[nrow][nchar] = Tile::DoorNext;
        m_doorNextPos = {nchar * Settings::entityWidth,
                         nrow * Settings::entityHeight};
        break;
      case 'P':
        m_map[nrow][nchar] = Tile::DoorPrev;
        m_doorPrevPos = {nchar * Settings::entityWidth,
                         nrow * Settings::entityHeight};
        break;
      case '1':
        m_enemies[m_enemiesSize++] =
            Enemy(Enemy::Type::First_Enemy, nchar * Settings::entityWidth,
                  nrow * Settings::entityHeight);
        m_map[nrow][nchar] = Tile::Empty;
        break;
      case '2':
        m_enemies[m_enemiesSize++] =
            Enemy(Enemy::Type::Second_Enemy, nchar * Settings::entityWidth,
                  nrow * Settings::entityHeight);
        m_map[nrow][nchar] = Tile::Empty;
        break;
      default:
        m_map[nrow][nchar] = Tile::Empty;
        break;
      }

      nchar++;
    }
  }

  // controllo numero caratteri ultima riga
  if (nchar < Settings::mapCols)
    Nc::stopWithError(1, "Invalid map: incorrect number of columns.");

  // controllo numero righe
  if (nrow != Settings::mapRows - 1)
    Nc::stopWithError(1, "Invalid map: incorrect number of rows.");

  file.close();
}

void Level::drawWalls(Nc::Window &window) const {
  for (int y = 0; y < Settings::mapRows; y++) {
    for (int x = 0; x < Settings::mapCols; x++) {
      int drawX = x * Settings::entityWidth;
      int drawY = y * Settings::entityHeight;

      if (m_map[y][x] == Tile::Wall)
        window.draw(s_wallSprite, drawX, drawY);

      else if (m_map[y][x] == Tile::DoorNext)
        window.draw(s_doorNextSprite, drawX, drawY);

      else if (m_map[y][x] == Tile::DoorPrev)
        window.draw(s_doorPrevSprite, drawX, drawY);

      else if (m_map[y][x] == Tile::BreakableWall)
        window.draw(s_breakableWallSprite, drawX, drawY);
    }
  }
}

void Level::addBomb(Bomb &bomb) {
  if (m_bombsSize >= s_maxLengthArrays)
    Nc::stopWithError(1, "Bombs array capacity exceeded.");

  while (bomb.getX() % Settings::entityWidth != 0)
    bomb.setPos(bomb.getX() + 1, bomb.getY());

  while (bomb.getY() % Settings::entityHeight != 0)
    bomb.setPos(bomb.getX(), bomb.getY() + 1);

  m_bombs[m_bombsSize++] = bomb;
}

void Level::getExplosionCells(const Bomb &bomb, Nc::Point cells[],
                              int &count) const {
  count = 0;

  int r = bomb.getRadius();
  int x = bomb.getX() / Settings::entityWidth;
  int y = bomb.getY() / Settings::entityHeight;

  const int dirs[4][2]{{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

  // centro
  cells[count++] = {x, y};

  for (int d = 0; d < 4; d++) {
    for (int k = 1; k <= r; k++) {
      int nx = x + dirs[d][0] * k;
      int ny = y + dirs[d][1] * k;

      // bounds check
      if (nx < 0 || nx >= Settings::mapCols || ny < 0 ||
          ny >= Settings::mapRows)
        break;

      Tile tile = m_map[ny][nx];

      if (tile == Tile::Wall)
        break;

      if (tile == Tile::BreakableWall) {
        if (bomb.hasExploded())
          break;
        else {
          cells[count++] = {nx, ny};
          break;
        }
      }

      cells[count++] = {nx, ny};
    }
  }
}

void Level::applyExplosion(const Nc::Point cells[], int count, Player &player) {
  for (int i = 0; i < count; i++) {
    int x = cells[i].x;
    int y = cells[i].y;

    Tile &tile = m_map[y][x];

    if (tile == Tile::BreakableWall)
      tile = Tile::Empty;

    for (int j = m_enemiesSize - 1; j >= 0; j--) {
      Entity explosion{x * Settings::entityWidth, y * Settings::entityHeight};

      // se devo togliere un nemico lo posiziono in fondo e decremento la size
      if (explosion.collide(m_enemies[j])) {
        m_enemiesSize--;
        m_enemies[j] = m_enemies[m_enemiesSize];

        player.addPoints(m_enemies[j].getEnemyPoints());
      }
    }

    // player
    Entity explosion{x * Settings::entityWidth, y * Settings::entityHeight};
    if (explosion.collide(player))
      player.onHit();
  }
}

void Level::drawExplosion(const Nc::Point cells[], int count,
                          Nc::Window &window) {
  for (int i = 0; i < count; i++) {
    window.draw(s_explosionSprite, cells[i].x * Settings::entityWidth,
                cells[i].y * Settings::entityHeight);
  }
}

void Level::handleBombs(Player &player) {
  for (int i = 0; i < m_bombsSize; i++) {
    Bomb &bomb = m_bombs[i];

    if (bomb.getStatus() == Bomb::Status::Exploding) {
      if (bomb.hasExploded())
        continue;

      Nc::Point cells[Bomb::s_maxExplosionCells];
      int count;

      getExplosionCells(bomb, cells, count);
      bomb.setExplosionCells(cells, count);
      applyExplosion(cells, count, player);
      bomb.setExploded(true);
    } else if (bomb.getStatus() == Bomb::Status::Finished) {
      // porto la bomba da rimuovere in fondo per eliminarla
      m_bombsSize--;
      m_bombs[i] = m_bombs[m_bombsSize];
      // ora nella posizione i-esima ho la prossima bomba da controllare
      i--;

      player.restoreBomb();
    }
  }
}

void Level::drawBombs(Nc::Window &window) {
  for (int i = 0; i < m_bombsSize; i++) {
    Bomb &bomb = m_bombs[i];
    if (bomb.getStatus() == Bomb::Status::Placed) {
      bomb.draw(window);
    } else if (bomb.getStatus() == Bomb::Status::Exploding) {
      drawExplosion(bomb.getExplosionCells(), bomb.getExplosionCount(), window);
    }
  }
}

int Level::getLevelNumber() const { return m_levelNumber; }

bool Level::shouldGoNextLevel() const { return m_shouldGoNext; }

bool Level::shouldGoPrevLevel() const { return m_shouldGoPrev; }

Nc::Point Level::getDoorPrevPos() const { return m_doorPrevPos; }

Nc::Point Level::getDoorNextPos() const { return m_doorNextPos; }

bool Level::checkIsWall(int x, int y) const {
  return m_map[y][x] == Tile::Wall || m_map[y][x] == Tile::BreakableWall ||
         m_map[y][x] == Tile::DoorNext || m_map[y][x] == Tile::DoorPrev;
}

bool Level::checkWallCollision(const Entity &entity) const {
  int width{Settings::entityWidth};
  int height{Settings::entityHeight};

  int x = entity.getX();
  int y = entity.getY();

  if (checkIsWall(x / width, y / height))
    return true;

  if (x % width != 0 && y % height != 0)
    if (checkIsWall(x / width + 1, y / height + 1))
      return true;

  if (x % width != 0)
    if (checkIsWall(x / width + 1, y / height))
      return true;

  if (y % height != 0)
    if (checkIsWall(x / width, y / height + 1))
      return true;

  return false;
}

bool Level::checkDoorNextCollision(const Entity &entity) const {
  Entity door{m_doorNextPos.x, m_doorNextPos.y};
  return entity.collide(door);
}

bool Level::checkDoorPrevCollision(const Entity &entity) const {
  Entity door{m_doorPrevPos.x, m_doorPrevPos.y};
  return entity.collide(door);
}

void Level::movePlayer(Player &player, Direction dir) {
  // Non controlliamo player.shouldMove() perché il suo delay deve essere sempre
  // 0
  player.move(dir);

  if (checkDoorNextCollision(player))
    m_shouldGoNext = true;
  else
    m_shouldGoNext = false;

  if (checkDoorPrevCollision(player))
    m_shouldGoPrev = true;
  else
    m_shouldGoPrev = false;

  // muovo di 1, per poter sempre arrivare al bordo del muro indipendentemente
  // dalla velocità
  while (checkWallCollision(player))
    player.Movable::move(getOppositeDir(dir), 1);
}

void Level::start() {
  m_shouldGoNext = false;
  m_shouldGoPrev = false;

  // start tempo e altra roba (?)
}

void Level::pause() {
  // stop del tempo
}

void Level::drawEnemies(Nc::Window &window) const {
  for (int i = 0; i < m_enemiesSize; i++) {
    const Enemy &enemy = m_enemies[i];
    enemy.draw(window);
  }
}

void Level::moveEnemies() {
  for (int i = 0; i < m_enemiesSize; i++) {
    Enemy &enemy = m_enemies[i];

    // Se il nemico non si deve muover passa all'iterazione successiva (prossimo
    // nemico)
    if (!enemy.shouldMove())
      continue;

    enemy.move();

    //booleano per controllare se la bomba collide con enemy
    bool bombCollide = false;
    for (int k = 0; k< m_bombsSize && !bombCollide; k++){
      Bomb &bomb = m_bombs[k];
      if (bomb.getStatus() == Bomb::Status::Placed && bomb.collide(enemy)) 
        bombCollide = true;
    }
    if (checkWallCollision(enemy) || bombCollide == true) {
      Direction prevDir = enemy.getDirection();
      enemy.setDirection(getOppositeDir(prevDir));
      enemy.move();

      do {
        enemy.setDirection(static_cast<Direction>(Random::get(1, 4)));
      } while (enemy.getDirection() == prevDir);
    }
  }
}

void Level::handleEnemies(Player &player) {
  for (int i = 0; i < m_enemiesSize; i++) {
    Enemy &enemy = m_enemies[i];

    if (player.collide(enemy)) {
      player.onHit();
    }
  }
}

Item Level::getItem(const Entity &entity) {
  for (int i{0}; i < m_itemsSize; i++) {
    Item &item{m_items[i]};

    if (entity.collide(item)) {
      return item;
    }
  }

  return Item{}; // restituisce item nullo
}

