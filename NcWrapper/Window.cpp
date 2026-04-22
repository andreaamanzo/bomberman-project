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

    refresh();
  }

  void Window::drawBox()
  {
    box(m_window, 0, 0);

    int start{ (m_width + 2 - (static_cast<int>(strlen(m_title)) + 2)) / 2 };
  
    mvwprintw(m_window, 0, start, " %s ", m_title);
  }

  void Window::setBgColor(Color color)
  {
    m_bgColor = color;
    short id{ Nc::getColorPair(Color::White, m_bgColor) };
    m_bgColorPairId = id;
  }
  
  void Window::setTitle(const char* title)
  {
    strncpy(m_title, title, 63);
    m_title[63] = '\0';
  }

  void Window::draw(const Sprite2x3& sprite, int x, int y)
  {
    Color bgColor{ sprite.getBgColor() != Color::Default ? sprite.getBgColor() : m_bgColor };
    short id{ Nc::getColorPair(sprite.getColor(), bgColor) };
    wattron(m_window, COLOR_PAIR(id));
    mvwaddstr(m_window, y + 1, x + 1, sprite.getRow0());
    mvwaddstr(m_window, y + 2, x + 1, sprite.getRow1());
    wattroff(m_window, COLOR_PAIR(id));
  }

  void Window::write(const char* string, int x, int y, Color color)
  {
    short id{ Nc::getColorPair(color, m_bgColor) };
    wattron(m_window, COLOR_PAIR(id));
    mvwaddstr(m_window, y + 1, x + 1, string);
    wattroff(m_window, COLOR_PAIR(id));
  }

  void Window::writeInt(int n, int x, int y, Color color)
  {
    short id{ Nc::getColorPair(color, m_bgColor) };
    wattron(m_window, COLOR_PAIR(id));
    mvwprintw(m_window, y + 1, x + 1, "%d", n);
    wattroff(m_window, COLOR_PAIR(id));
  }
  
  void Window::display()
  {
    drawBox();
    wrefresh(m_window);
  }
  
  void Window::clear()
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

  void Window::getUserInput(int posX, int posY, char* buff, int buffLength)
  {
    if (buffLength <= 1) return;

    nodelay(stdscr, FALSE);
    curs_set(1);
    echo();

    wmove(m_window, posY + 1, posX + 1);
    
    int i = 0;
    
    while (i < buffLength - 1)
    {
      int c = wgetch(m_window);
      if (c == KEY_ENTER || c == 10) break;

      buff[i] = c;
      i++;
    }
    buff[i] = '\0';

    nodelay(stdscr, TRUE);
    curs_set(0);
    noecho();
  }
}
