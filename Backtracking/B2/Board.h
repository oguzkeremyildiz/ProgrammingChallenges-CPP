//
// Created by Oğuz Kerem Yıldız on 27.12.2020.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_BOARD_H
#define PROGRAMMINGCHALLENGES_CPP_BOARD_H
#include <fstream>

using namespace std;

class Board {
private:
    int **items;
    int x;
    int y;
public:
    Board();
    Board(fstream& file);
    int point();
    long hash();
    bool isASolution();
    Board clone();
    int getX();
    int getY();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
};

#endif //PROGRAMMINGCHALLENGES_CPP_BOARD_H
