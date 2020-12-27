//
// Created by Oğuz Kerem Yıldız on 27.12.2020.
//

#include <cstdlib>
#include "Board.h"

using namespace std;

Board::Board() {
    items = (int **)malloc(4 * sizeof(int *));
    for (int i = 0; i < 4; i++) {
        items[i] = (int*) malloc(4 * sizeof(int));
    }
}

Board::Board(fstream& file) {
    items = (int **)malloc(4 * sizeof(int *));
    for (int i = 0; i < 4; i++) {
        items[i] = (int*) malloc(4 * sizeof(int));
    }
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
            file >> items[j][k];
            if (items[j][k] == 0) {
                x = j;
                y = k;
            }
        }
    }
}

int Board::point() {
    int solvedBoard[4][4] {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 0},
    };
    int point = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int item = solvedBoard[i][j];
            bool found = false;
            for (int k = 0; k < 4; k++) {
                for (int l = 0; l < 4; l++) {
                    if (item == items[k][l]) {
                        point += abs(i - k) + abs(j - l);
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
        }
    }
    return point;
}

long Board::hash() {
    long code = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            code = code * 16 + items[i][j];
        }
    }
    return code;
}

bool Board::isASolution() {
    int solvedBoard[4][4] {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 0},
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (solvedBoard[i][j] != items[i][j]) {
                return false;
            }
        }
    }
    return true;
}

Board Board::clone() {
    Board clone = Board();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            clone.items[i][j] = items[i][j];
        }
    }
    clone.x = x;
    clone.y = y;
    return clone;
}

int Board::getX() {
    return x;
}

int Board::getY() {
    return y;
}

void Board::moveLeft() {
    int tmp = items[x][y];
    items[x][y] = items[x][y - 1];
    items[x][y - 1] = tmp;
    y--;
}

void Board::moveRight() {
    int tmp = items[x][y];
    items[x][y] = items[x][y + 1];
    items[x][y + 1] = tmp;
    y++;
}

void Board::moveUp() {
    int tmp = items[x][y];
    items[x][y] = items[x - 1][y];
    items[x - 1][y] = tmp;
    x--;
}

void Board::moveDown() {
    int tmp = items[x][y];
    items[x][y] = items[x + 1][y];
    items[x + 1][y] = tmp;
    x++;
}