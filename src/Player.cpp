#include "Player.hpp"
#include "Bomb.hpp"

Player::Player(int lives, int x, int y)
  : Movable{ s_playerSprite, x, y, 0 }
  , m_respawnPoint{ x, y }
  , m_lives{ lives }
{ }

void Player::move(Direction dir)
{
  Movable::move(dir, 1);
}

Bomb Player::placeBomb()
{
  if (m_placedBombs >= m_maxBombs) return Bomb{};

  m_placedBombs++;
  
  return Bomb{ m_x, m_y, m_bombRadius };
}

void Player::restoreBomb()
{
  if (m_placedBombs > 0)
    m_placedBombs--;
}

void Player::restoreAllBombs()
{
  m_placedBombs = 0;
}

void Player::setRespownPoint(int x, int y)
{
  m_respawnPoint = { x, y };
}

void Player::atRespown()
{
  setPos(m_respawnPoint.x, m_respawnPoint.y);
}

void Player::onHit()
{
  if (!m_isInvincible)
  {
    m_lives--;
    atRespown();

    Item respawnInvulnerability{ Item::Type::Invulnerability, 0, 0};
    respawnInvulnerability.setPowerDuration(3);
    collectItem(respawnInvulnerability);
  }
}

bool Player::isAlive() const 
{
  return m_lives > 0;
}

void Player::collectItem(const Item& item)
{
  switch (item.getType())
  {
  case Item::Type::Null :
    return;
  
  case Item::Type::IncrementBombRadius :
    m_bombRadius++;
    break;

  case Item::Type::IncrementMaxBombs :
    m_maxBombs++;
    break;

  case Item::Type::Invulnerability :
    m_sprite.setColor(Nc::Color::Purple);
    m_isInvincible = true;
    break;

  case Item::Type::TimedIncrementBombPower :
    m_bombRadius += 3;
    m_maxBombs   += 2;
    break;

  case Item::Type::OneUp :
    m_lives++;
    break;
  }

  // lo aggiungo alla lista di item del player
  m_items[m_itemsSize] = item;
  if (m_items[m_itemsSize].isTimed()) m_items[m_itemsSize].activate();
  m_itemsSize++;
}

void Player::addPoints(int points) 
{
  m_points += points;
}

int Player::getPoints() const { return m_points; }
  
int Player::getLives() const { return m_lives; }

int Player::getBombRadius() const { return m_bombRadius; }

int Player::getMaxBombs() const { return m_maxBombs; }

int Player::getPlacedBombs() const { return m_placedBombs; }

const Item* Player::getItemsList() const
{
  return m_items;
}

int Player::getItemsListSize() const
{
  return m_itemsSize;
}

void Player::handleItems()
{
  for (int i{ 0 } ; i < m_itemsSize ; i++)
  {
    // annullo l'effetto dell'item
    if (!m_items[i].isActive())
    {
      switch (m_items[i].getType())
      {
      case Item::Type::TimedIncrementBombPower :
        m_bombRadius -= 3;
        m_maxBombs   -= 2;
        break;
      
      case Item::Type::Invulnerability :
        m_isInvincible = false;
        m_sprite.setColor(Nc::Color::Green);
        break;
      
      default : break;
      }

      // sovrascrivo item da eliminare con ultimo item e decremento la size
      m_itemsSize--;
      m_items[i] = m_items[m_itemsSize];

      // decremento la i per controllare l'elemento appena inserito
      i--;
    }
  }
}