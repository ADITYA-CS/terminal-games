
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
/**
 * matrix_ cell value means
 * 1 to 8: no of bombs in surrounding cells, visible to player
 * -1 to -8: no of bombs in surrounding cells, but not visible to player
 * 9 :  bomb
 */
class Board {
private:
    vector<vector<int>> matrix_;
    int bomb_count_;
    int moves_;
private:
    void FirstMoveDestroy(const int, const int, int&);
public:
    explicit Board(int);
    void FirstMove(const int, const int);
    int Cell(const int,const int);
    void UpdateCell(const int, const int);
    bool WasLast();
};

Board::Board(int n) {
    matrix_.resize(9, vector<int>(9,-10));
    bomb_count_ = 9 * 9 * 25 / 100;
    moves_ = n * n - bomb_count_;
}

void Board::FirstMove(const int r, const int c) {
    srand(time(NULL));
    int row = matrix_.size();
    int col = matrix_[0].size();
    // placing bombs
    for (int i = 0, x, y; i < bomb_count_; i++){
        y = rand() % row;
        x = rand() % col;
        if(matrix_[y][x] != -10|| (r == y && c == x)) {
            i--;
            continue;
        }
        matrix_[y][x] = 9;
    }
    // counting no of bombs in surrounding cells
    for (int i = 0; i < row; i++) {
        for (int j = 0, c; j < col; j++) {
            c = 0;
            //top left corner
            if(j - 1 >= 0 && i - 1 >= 0)
                c += matrix_[i - 1][j - 1] == 9;
            // top
            if(i - 1 >= 0)
                c += matrix_[i - 1][j] == 9;
            // top right corner
            if(j + 1 < col && i - 1 >= 0)
                c += matrix_[i - 1][j + 1] == 9;
            // left
            if(j - 1 >= 0)
                c += matrix_[i][j - 1] == 9;
            // right
            if(j + 1 < col)
                c += matrix_[i][j + 1] == 9;
            // bottom left
            if(j - 1 >= 0 && i + 1 < row)
                c += matrix_[i + 1][j - 1] == 9;
            // bottom
            if(i + 1 < row)
                c += matrix_[i + 1][j] == 9;
            // bottom right
            if(j + 1 < col && i + 1 < row)
                c += matrix_[i + 1][j + 1] == 9;
            if(matrix_[i][j] != 9 && c)
                matrix_[i][j] = -1 * c;
        }
    }
    int explode = 5;
    FirstMoveDestroy(r, c, explode);
}

int Board::Cell(int i, int j) {
    return matrix_[i][j];
}

void Board::FirstMoveDestroy(const int r, const int c, int &no) {
    if(!no || r < 0 || r >= matrix_.size()
        || c < 0 || c >= matrix_[0].size() || matrix_[r][c] == 9)
        return;

    UpdateCell(r, c);
    no--;
    refresh();
    FirstMoveDestroy(r-1, c-1, no);
    FirstMoveDestroy(r-1, c, no);
    FirstMoveDestroy(r-1, c+1, no);
    FirstMoveDestroy(r, c-1, no);
    FirstMoveDestroy(r, c+1, no);
    FirstMoveDestroy(r+1, c-1, no);
    FirstMoveDestroy(r+1, c, no);
    FirstMoveDestroy(r+1, c+1, no);
}

void Board::UpdateCell(const int r, const int c) {
    matrix_[r][c] *= -1;
    if(matrix_[r][c] == 10)
        matrix_[r][c] = 0;
    moves_ -= 1;
}

bool Board::WasLast() {
    return !moves_;
}
