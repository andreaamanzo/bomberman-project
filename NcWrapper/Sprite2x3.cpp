#include "Sprite2x3.hpp"
#include <ncurses.h>

namespace Nc
{
  Sprite2x3::Sprite2x3(const char* r0, const char* r1, Color color, Color bgColor)
    : m_rows{ r0, r1 }
    , m_color{ color }
    , m_bgColor{ bgColor }
  { }
  
  Color Sprite2x3::getColor() const
  {
    return m_color;
  }

  Color Sprite2x3::getBgColor() const
  {
    return m_bgColor;
  }

  const char* Sprite2x3::getRow0() const
  {
    return m_rows[0];
  }
  const char* Sprite2x3::getRow1() const
  {
    return m_rows[1];
  }
  
  void Sprite2x3::setColor(Color color)
  {
    m_color = color;
  }

  void Sprite2x3::setBgColor(Color color)
  {
    m_bgColor = color;
  }
}
