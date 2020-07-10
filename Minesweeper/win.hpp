#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>

using namespace std;
// Function declaration
void WinWindow();


// Funciton definition
void WinWindow() {
  srand(time(NULL));
  WINDOW* win = newwin(0, 0, 0, 0);
  init_pair(1, COLOR_WHITE,COLOR_RED);
  init_pair(2, COLOR_WHITE,COLOR_YELLOW);
  init_pair(3, COLOR_WHITE,COLOR_BLUE);
  init_pair(4, COLOR_WHITE,COLOR_CYAN);
  init_pair(5, COLOR_CYAN, COLOR_BLACK);
  init_pair(0, COLOR_CYAN, COLOR_WHITE);
  wbkgd(win, COLOR_PAIR(5));

  int row, col;
  getmaxyx(win, row, col);
  int density = row * col * 30 / 100;
  while (density > 0) {
    density--;
    int r = rand() % (row+1);
    int c = rand() % (col+1);
    mvwaddch(win, r, c, '*');
    napms(1);
    wrefresh(win);
  }
  wattron(win, A_BLINK | A_BOLD);
  mvwaddstr(win, row / 2 - 1, col / 2 - 6, "          ");
  mvwaddstr(win, row / 2, col / 2 - 6, " You won ");
  mvwaddstr(win, row / 2 + 1, col / 2 - 6, "          ");
  wrefresh(win);
  wattroff(win,A_BOLD);
}
// int main() {
//   initscr();
//   refresh();
//   curs_set(0);
//   start_color();
//   noecho();
//   WinWindow();
//   getch();
//   endwin();
//
// }
