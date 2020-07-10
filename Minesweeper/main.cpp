
#include <iostream>
#include <cstring>
#include <ncurses.h>

#include "welcome.hpp"
#include "board.hpp"
#include "fail.hpp"
#include "win.hpp"

using namespace std;
#define STDSCR_FB 7

void SetWindow();
void Color();
vector<vector<WINDOW*>> Subwindow();
void Game();
void PrintBoard(Board &board, vector<vector<WINDOW*>> &subwindow);
void PrintFailBoard(Board &board, vector<vector<WINDOW*>> &subwindow);

int main(int argc, char const *argv[]) {
    SetWindow();
    int r, c;
    getmaxyx(stdscr, r, c);
    if(r < 23 || c < 50) {
      addstr("Terminal window size must be atleast 50x23\n");
      refresh();
      getch();
      endwin();
      exit(1);
    }
    Welcome();
    touchwin(stdscr);
    Game();
    getch();
    endwin();
}

void SetWindow() {
    initscr();
    mmask_t mmask = mousemask(ALL_MOUSE_EVENTS, NULL);
    if(!mmask){
        std::cerr << "Terminal does not support Mouse movement" << '\n';
        endwin();
        exit(1);
    }
    curs_set(0);
    start_color();
    Color();
    noecho();
    keypad(stdscr,TRUE);
    bkgd(COLOR_PAIR(STDSCR_FB));
    box(stdscr, 0, 0);
    refresh();
}

void Color() {
    init_pair(STDSCR_FB, COLOR_CYAN, COLOR_BLACK);
    init_pair(1, COLOR_WHITE,COLOR_RED);
    init_pair(2, COLOR_WHITE,COLOR_YELLOW);
    init_pair(3, COLOR_WHITE,COLOR_BLUE);
    init_pair(4, COLOR_WHITE,COLOR_CYAN);
    init_pair(8, COLOR_CYAN, COLOR_WHITE);
}

vector<vector<WINDOW*>> Subwindow() {
    int row, col;
    getmaxyx(stdscr, row, col);
    int left_corner_row = row / 2 - 9;
    int left_corner_col = col / 2 - 18;

    vector<vector<WINDOW*>> sub(9, vector<WINDOW*>(9));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sub[i][j] = subwin(stdscr, 2, 4, left_corner_row + 2 * i,
                left_corner_col + 4 * j);
            wbkgd(sub[i][j], COLOR_PAIR((i+j) % 4 + 1));
            wrefresh(sub[i][j]);
        }
    }
    return sub;
}

void Game() {
    Board minesweeper(9);
    auto subwindow = Subwindow();
    MEVENT mort;
    int ch, r, c;
    int row, col;
    getmaxyx(stdscr, row, col);
    int left_corner_row = row / 2 - 9;
    int left_corner_col = col / 2 - 18;
    bool first_move = true;
    long point  = 0;

    while (true) {
        PrintBoard(minesweeper, subwindow);
        ch = getch();
        if (ch == 'q' || ch == 'Q') {
            endwin();
            exit(0);
        } else if(ch == 'h' || ch == 'H') {
          PrintHelp();
          touchwin(stdscr);
        }
        if (ch == KEY_MOUSE) {
            getmouse(&mort);
            r = mort.y, c = mort.x;
            if (r < left_corner_row || r >= left_corner_row + 18
                || c < left_corner_col || c >= left_corner_col + 36) {
                    continue;
            }

            r = (r - left_corner_row) / 2;
            c = (c - left_corner_col) / 4;
            if (first_move) {
                minesweeper.FirstMove(r, c);
                first_move = false;
                continue;
            }
            if (minesweeper.Cell(r, c) == 9) {
              PrintFailBoard(minesweeper, subwindow);
                napms(100);
                FailWindow();
                break;
            } else if (minesweeper.Cell(r, c) < 0) {
                minesweeper.UpdateCell(r, c);
                point += 5;
            }
        }
        if(minesweeper.WasLast()) {
          WinWindow();
          break;
        }
    }
    getch();
}

void PrintBoard(Board &board, vector<vector<WINDOW*>> &subwindow) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(board.Cell(i, j) == 9 || board.Cell(i, j) < 0) {
                continue;
            }
            wbkgd(subwindow[i][j], COLOR_PAIR(8));
            mvwprintw(subwindow[i][j],1, 2, "%d", board.Cell(i, j));
            wrefresh(subwindow[i][j]);
        }
    }
}

void PrintFailBoard(Board &board, vector<vector<WINDOW*>> &subwindow) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if(board.Cell(i, j) == 9)
        continue;
      wbkgd(subwindow[i][j], COLOR_PAIR(8));
      int v = abs(board.Cell(i, j));
      if(v == 10)
        v = 0;
      mvwprintw(subwindow[i][j],1, 2, "%d", v);
      wrefresh(subwindow[i][j]);
      napms(100);
    }
  }
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      wbkgd(subwindow[i][j], COLOR_PAIR((i+j) % 4 + 1));
      wrefresh(subwindow[i][j]);
      napms(100);
    }
  }
}
