#include "Sprite2x3.hpp"
#include <ncurses.h>
#include <cwchar>
#include <cassert>

namespace Nc
{
  Sprite2x3::Sprite2x3(const wchar_t* r0, const wchar_t* r1, Color color, Color bgColor)
    : m_rows{ r0, r1 }
    , m_color{ color }
    , m_bgColor{ bgColor }
  {
    const int c0 = getNumCols(m_rows[0]);
    const int c1 = getNumCols(m_rows[1]);
  
    assert(c0 == s_width && c1 == s_width && "Sprite2x3: Each row must be 3 columns wide");
  }
  
  int Sprite2x3::getNumCols(const wchar_t* s)
  {
    if (!s) return -1;
    const std::size_t n = std::wcslen(s);
    return static_cast<int>(n);
    // return ::wcswidth(s, n);
  }
  
  Color Sprite2x3::getColor() const
  {
    return m_color;
  }

  Color Sprite2x3::getBgColor() const
  {
    return m_bgColor;
  }

  const wchar_t* Sprite2x3::getRow0() const
  {
    return m_rows[0];
  }
  const wchar_t* Sprite2x3::getRow1() const
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
