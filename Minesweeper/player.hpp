#ifndef MINESWEEPER_PLAYER
#define MINESWEEPER_PLAYER

#include <iostream>

using namespace std;

class Player{
private:
    string name_;
    long score_;
public:
    Player();
    string Getname();
    long GetScore();
    friend bool  operator<(const Player &, const Player &);
    friend ostream& operator<<(ostream &, const Player &);
    friend istream& operator>>(istream &, Player &);
};

Player::Player() {
    name_ = "";
    score_ = 0;
}

string Player::Getname() {
    return name_;
}

long Player::GetScore() {
    return score_;
}

bool  operator<(const Player &a, const Player &b) {
    return a.score_ <= b.score_;
}

ostream& operator<<(ostream &out, const Player &player) {
    out << player.name_ << endl << player.score_ << endl;
    return out;
}
istream& operator>>(istream &in, Player &player) {
    in >> player.name_ >> player.score_;
    return in;
}



// int main() {
//     // auto path = fs::current_path();
//     // path /= "player.txt";
//     // ifstream in(path);
//     // path += ".txt";
//     // cout << path << endl;
//     // ofstream out(path);
//     // Player p;
//     // while(in){
//     //     in >> p;
//     //     out << p;
//     // }
//     // out.close();
//     // in.close();
//     Player a, b;
//     cin >> a >> b;
//     cout << (a < b);
// }
#endif
