#include "Window.hpp"
#include "Sprite2x3.hpp"
#include "ColorPair.hpp"
#include <ncurses.h>
#include <cstring>

namespace Nc
{
  Window::Window(int width, int height, int start_x, int start_y)
    : m_window{ newwin(height + 2, width + 2, start_y, start_x) }
    , m_width { width }
    , m_height{ height }
    , m_startX{ start_x }
    , m_startY{ start_y }
  {
    short id{ Nc::getColorPair(Color::White, m_bgColor) };
    m_bgColorPairId = id;
    box(m_window, 0, 0);
    refresh();
    wrefresh(m_window);
  }

  void Window::setBgColor(Color color)
  {
    m_bgColor = color;
    short id{ Nc::getColorPair(Color::White, m_bgColor) };
    m_bgColorPairId = id;
  }
  
  void Window::setTitle(const char* title) const
  {
    int start{ (m_width + 2 - (static_cast<int>(strlen(title)) + 2)) / 2 };
  
    mvwprintw(m_window, 0, start, " %s ", title);
    wrefresh(m_window);
  }

  void Window::draw(const Sprite2x3& sprite, int x, int y) const
  {
    Color bgColor{ sprite.getBgColor() != Color::Default ? sprite.getBgColor() : m_bgColor };
    short id{ Nc::getColorPair(sprite.getColor(), bgColor) };
    wattron(m_window, COLOR_PAIR(id));
    mvwaddwstr(m_window, y + 1, x + 1, sprite.getRow0());
    mvwaddwstr(m_window, y + 2, x + 1, sprite.getRow1());
    wattroff(m_window, COLOR_PAIR(id));
  }

  void Window::write(const char* string, int x, int y, Color color) const
  {
    short id{ Nc::getColorPair(color, m_bgColor) };
    wattron(m_window, COLOR_PAIR(id));
    mvwaddstr(m_window, y + 1, x + 1, string);
    wattroff(m_window, COLOR_PAIR(id));
  }
  
  void Window::display() const
  {
    wrefresh(m_window);
  }
  
  void Window::clear() const
  {
    wattron(m_window, COLOR_PAIR(m_bgColorPairId));
    for (int y = 1; y <= m_height; y++)
      for (int x = 1; x <= m_width; x++)
        mvwaddch(m_window, y, x, ' ');

    wattroff(m_window, COLOR_PAIR(m_bgColorPairId));
  }
  
  int Window::getWidth() const
  {
    return m_width;
  }
  
  int Window::getHeight() const
  {
    return m_height;
  }

  Point Window::getPos() const
  {
    return Point{ m_startX, m_startY };
  }
}
