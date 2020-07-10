#ifndef MINESWEEPER_WELCOME
#define MINESWEEPER_WELCOME

#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <vector>
#include <filesystem>
#include <fstream>
#include "player.hpp"

using namespace std;
namespace fs = std::filesystem;

// Function declaration
void Welcome();
void PrintHelp();
void PrintTopTenPlayer(WINDOW *win, int rows, int cols);
void WriteInCenter(WINDOW *win, int rows, int cols, char *str, attr_t attr);
char * StringToCharStar(const string &str);

// define
#define WELCOME_FB 5
#define HELP_FB 6

// Function Definition
void Welcome() {
    WINDOW *welcome = newwin(0, 0, 0, 0);
    init_pair(WELCOME_FB, COLOR_CYAN, COLOR_BLACK);
    wbkgd(welcome, COLOR_PAIR(WELCOME_FB));
    box(welcome, 0, 0);
    wrefresh(welcome);

    int rows, cols;
    getmaxyx(welcome, rows, cols);
    WriteInCenter(welcome, 5, cols, StringToCharStar("Welcome To Minesweeper"), A_BOLD);
    PrintTopTenPlayer(welcome, rows / 2, cols);
    WriteInCenter(welcome, rows - 3, cols, StringToCharStar("Press any key to start"), A_BOLD);
    getch();
}

void WriteInCenter(WINDOW *win, int rows, int cols, char *str, attr_t attr = A_NORMAL) {
    int len = strlen(str);
    attrset(A_BOLD);
    mvwaddstr(win, rows, (cols - len) / 2, str);
    attroff(A_BOLD);
    wrefresh(win);
}

void PrintTopTenPlayer(WINDOW *win, int rows, int cols) {
    mvwaddstr(win, rows - 3, cols /2 - 15, "Player");
    mvwaddstr(win, rows - 3, cols /2 + 15, "Score");
    wrefresh(win);

    auto path = fs::current_path();
    path /= "player.txt";
    ifstream in(path);
    Player player;
    for(int i = 0; i < 10; i++) {
        in >> player;
        mvwprintw(win, rows - 1 + i, cols / 2 - 15, "%s", StringToCharStar(player.Getname()));
        mvwprintw(win, rows - 1 + i, cols / 2 + 15, "%ld", player.GetScore());
        wrefresh(win);
    }
    in.close();
}

void PrintHelp() {
    int cols, rows;
    WINDOW * help = newwin(0, 0, 0, 0);
    getmaxyx(help, rows, cols);
    init_pair(HELP_FB, COLOR_BLACK, COLOR_CYAN);
    wbkgd(help, COLOR_PAIR(HELP_FB));
    box(help, 0, 0);
    wrefresh(help);

    char rule_1[] = "1. First mine will not have explosion.";
    char rule_2[] = "2. Each cell number represents the number of surrounding bombs.";
    char rule_3[] = "3. Every successful step gives you one point.";

    WriteInCenter(help, rows / 2 - 2, cols, StringToCharStar("Rules"));
    mvwaddstr(help, rows / 2, 10, rule_1);
    mvwaddstr(help, rows / 2 + 1, 10, rule_2);
    mvwaddstr(help, rows / 2 + 2, 10, rule_3);
    WriteInCenter(help, rows - 3, cols, StringToCharStar("Press any key to return"));
    wrefresh(help);
    getch();
    delwin(help);
}

char * StringToCharStar(const string &str){
    int len = str.size();
    char *c_str = new char[len+1];
    for(int i = 0; i < len; i++) {
        c_str[i] = str[i];
    }
    c_str[len] = '\0';
    return c_str;
}


#endif
