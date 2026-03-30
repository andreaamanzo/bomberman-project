#include "Enemy.hpp"
#include "Bomb.hpp"
#include "Entity.hpp"
#include "Level.hpp"
#include "Sprite2x3.hpp"

Enemy::Enemy(const Nc::Sprite2x3& s_enemySprite, int x, int y )
: Entity{s_enemySprite, x, y}
{}

void Enemy::move() {
    if (m_direction == 0) m_x = -1;
    else if (m_direction == 1) m_y = +1;
    else if (m_direction == 2) m_x = +1;
    else m_y = -1;
}
