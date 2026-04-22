#ifndef WINDOW_H
#define WINDOW_H

#include "Sprite2x3.hpp"
#include "NcTypes.hpp"
#include <ncurses.h>

namespace Nc
{
  class Window
  {
  public:
    Window() = default;
    Window(int width, int height, int start_x = 0, int start_y = 0);
    
    void setBgColor(Color color);
    void setTitle(const char* title);
    void draw(const Sprite2x3& sprite, int x, int y);
    void write(const char* string, int x, int y, Color color = Color::White);
    void writeInt(int n, int x, int y, Color color = Color::White);
    void display();
    void clear();
    int getWidth() const; 
    int getHeight() const;
    Point getPos() const;

  private:
    WINDOW* m_window{};
    Color m_bgColor{ Color::Default };
    short m_bgColorPairId{};
    int m_width{};
    int m_height{};
    int m_startX{};
    int m_startY{};
    char m_title[64];

    void drawBox();
  };
}

#endif