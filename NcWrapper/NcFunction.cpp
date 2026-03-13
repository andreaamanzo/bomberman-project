#include "NcFunctions.hpp"
#include <ncurses.h>
#include <clocale>
#include <thread>
#include <chrono>

namespace Nc
{
  void init()
  {
    std::setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    start_color();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // getch non è più bloccante
    curs_set(0);
  }
  
  void stop()
  {
    endwin();
  }

  int getTerminalWidth()
  {
    return getmaxx(stdscr);
  }

  int getTerminalHeight()
  {
    return getmaxy(stdscr);
  }

  void sleepFor(int milliseconds)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds{ milliseconds });
  }
  
  Key getKeyPressed()
  {
    int c = getch();

    if (c == ERR)
      return Key::None;

    switch (c) 
    {
      case KEY_UP:    return Key::Up;
      case KEY_DOWN:  return Key::Down;
      case KEY_LEFT:  return Key::Left;
      case KEY_RIGHT: return Key::Right;

      case 10:         
      case KEY_ENTER:  return Key::Enter;

      case 27:        
          return Key::Escape;

      case ' ':
          return Key::Space;

      case 127:
      case KEY_BACKSPACE:
          return Key::Backspace;
    }

    if (c >= 'a' && c <= 'z')
      c = c - 'a' + 'A';

    if (c >= 'A' && c <= 'Z') 
    {
      int offset = c - 'A';
      int base   = static_cast<int>(Key::A);
      return static_cast<Key>(base + offset);
    }

    return Key::None;
  }
}  