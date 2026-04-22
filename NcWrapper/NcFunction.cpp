#include "NcFunctions.hpp"
#include <ncurses.h>
#include <clocale>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>

namespace Nc
{
  static void initDefaultColors()
  {
    if (!has_colors())
      stopWithError(1, "Terminal does not support colors.");

    start_color();
    use_default_colors();

    if (!can_change_color())
      stopWithError(1, "Your terminal does not support custom colors required by the game.");

    // base
    init_color(COLOR_BLACK,   0,   0,   0);
    init_color(COLOR_RED,     900, 100, 100);
    init_color(COLOR_GREEN,   100, 900, 100);
    init_color(COLOR_YELLOW,  900, 900, 200);
    init_color(COLOR_BLUE,    100, 100, 900);
    init_color(COLOR_MAGENTA, 900, 100, 900);
    init_color(COLOR_CYAN,    100, 900, 900);
    init_color(COLOR_WHITE,   900, 900, 900);

    // custom palette
    init_color(8,  1000, 450, 0);   // Orange
    init_color(9,  300, 300, 300);  // DarkGray
    init_color(10, 700, 700, 700);  // LightGray
    init_color(11, 1000, 400, 700); // Pink
    init_color(12, 500, 1000, 200); // Lime
    init_color(13, 400, 700, 1000); // Sky
    init_color(14, 600, 200, 900);  // Purple
    init_color(15, 1000, 800, 200); // Gold
    init_color(16, 1000, 300, 0);   // Fire
    init_color(17,  800, 600, 300); // Light Brown
    init_color(18,  650, 300, 150); // Brick
  }

  void init()
  {
    std::setlocale(LC_ALL, "");
    std::srand(static_cast<unsigned int>(std::time(0)));
    
    initscr();
    initDefaultColors();
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

  void stopWithError(int exitCode, const char* msg)
  {
    endwin();
    std::cerr << "RUNTIME ERROR: " << msg << '\n';
    std::exit(exitCode);
  }

  int getTerminalWidth()
  {
    return getmaxx(stdscr);
  }

  int getTerminalHeight()
  {
    return getmaxy(stdscr);
  }

  void checkTerminalSize(int minWidth, int minHeight)
  {
    if (getTerminalHeight() < minHeight || getTerminalWidth() < minWidth)
    {
      stopWithError(1, "Terminal window is too small. Please resize it and try again.");
    }
  }

  void clearAll()
  {
    clear();
    refresh();
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

  Key waitForKeyPressd()
  {
    getch(); // "svuta il buffer (?)"
    nodelay(stdscr, FALSE);
    Key k = getKeyPressed();
    nodelay(stdscr, TRUE);

    return k;
  }
}  