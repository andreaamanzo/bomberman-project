#ifndef SPRITE_2X3_H
#define SPRITE_2X3_H

#include "NcTypes.hpp"
#include <ncurses.h>
#include <cwchar>
#include <cassert>

namespace Nc
{
  class Sprite2x3 
  {
  public:
    Sprite2x3() = default;
    Sprite2x3(const wchar_t* r0, const wchar_t* r1, Color color = Color::Default, Color bgColor = Color::Default);

    Color getColor() const;
    Color getBgColor() const;
    const wchar_t* getRow0() const;
    const wchar_t* getRow1() const;
    void setColor(Color color);
    void setBgColor(Color color);
  
  private:
    static constexpr int s_height = 2;
    static constexpr int s_width  = 3;
  
    const wchar_t* m_rows[s_height]{};
    Color m_color{ Color::White };
    Color m_bgColor{ Color::Default };
  
    static int getNumCols(const wchar_t* s);
  };
}


#endif