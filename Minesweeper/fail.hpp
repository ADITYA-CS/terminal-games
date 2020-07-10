#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>

using namespace std;
// Function declaration
void FailWindow();


// Funciton definition
void FailWindow() {
  srand(time(NULL));
  WINDOW* fail = newwin(0, 0, 0, 0);
  init_pair(1, COLOR_WHITE,COLOR_RED);
  init_pair(2, COLOR_WHITE,COLOR_YELLOW);
  init_pair(3, COLOR_WHITE,COLOR_BLUE);
  init_pair(4, COLOR_WHITE,COLOR_CYAN);
  init_pair(5, COLOR_CYAN, COLOR_BLACK);
  init_pair(0, COLOR_CYAN, COLOR_WHITE);
  wbkgd(fail, COLOR_PAIR(5));

  int row, col;
  getmaxyx(fail, row, col);
  int density = row * col * 20 / 100;
  string v{"&*(&*w#/-*/#$@^$)"};
  while (density > 0) {
    density--;
    int r = rand() % (row+1);
    int c = rand() % (col+1);
    int i = rand() % v.size();
    mvwaddch(fail, r, c, v[i]);
    napms(1);
    wrefresh(fail);
  }
  wattron(fail, A_BLINK | A_BOLD);
  mvwaddstr(fail, row / 2 - 1, col / 2 - 6, "          ");
  mvwaddstr(fail, row / 2, col / 2 - 6, " You lost ");
  mvwaddstr(fail, row / 2 + 1, col / 2 - 6, "          ");
  wrefresh(fail);
  wattroff(fail,A_BOLD);
}
// int main() {
//   initscr();
//   refresh();
//   curs_set(0);
//   start_color();
//   noecho();
//   FailWindow();
//   getch();
//   endwin();
// }
