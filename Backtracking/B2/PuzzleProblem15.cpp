//
// Created by Oğuz Kerem Yıldız on 27.12.2020.
//

#include <iostream>
#include <unordered_map>
#include "Board.h"
#include <vector>

using namespace std;

static bool finished = false;
static unordered_map<long, string> traversedWithLength;

string toString(vector<string> moves) {
    string string;
    for (int i = 0; i < moves.size(); i++) {
        string += moves.at(i);
    }
    return string;
}

vector<string> constructCandidates(Board board) {
    vector<string> subsets = vector<string>();
    int x = board.getX();
    int y = board.getY();
    vector<int> points = vector<int>();
    subsets.emplace_back("L");
    if (y - 1 > -1) {
        board.moveLeft();
        points.push_back(board.point());
        board.moveRight();
    } else {
        points.push_back(1000);
    }
    subsets.emplace_back("R");
    if (y + 1 < 4) {
        board.moveRight();
        points.push_back(board.point());
        board.moveLeft();
    } else {
        points.push_back(1000);
    }
    subsets.emplace_back("D");
    if (x + 1 < 4) {
        board.moveDown();
        points.push_back(board.point());
        board.moveUp();
    } else {
        points.push_back(1000);
    }
    subsets.emplace_back("U");
    if (x - 1 > -1) {
        board.moveUp();
        points.push_back(board.point());
        board.moveDown();
    } else {
        points.push_back(1000);
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (points.at(i) < points.at(j)) {
                int temporary = points.at(i);
                points.at(i) = points.at(j);
                points.at(j) = temporary;
                string stringTemporary = subsets.at(i);
                subsets.at(i) = subsets.at(j);
                subsets.at(j) = stringTemporary;
            }
        }
    }
    for (int i = 0; i < points.size(); i++) {
        if (points.at(i) == 1000) {
            points.erase(points.begin() + i);
            subsets.erase(subsets.begin() + i);
            i--;
        }
    }
    return subsets;
}

Board move(Board board, string move) {
    if (move == "L") {
        board.moveLeft();
    } else if (move == "R") {
        board.moveRight();
    } else if (move == "U") {
        board.moveUp();
    } else if (move == "D") {
        board.moveDown();
    }
    return board;
}

void backtrack(Board board, vector<string> moves, int maxPoint) {
    if (moves.size() > maxPoint) {
        return;
    }
    if (traversedWithLength.find(board.hash()) != traversedWithLength.end()) {
        if (traversedWithLength[board.hash()].length() < toString(moves).length()) {
            return;
        } else {
            traversedWithLength[board.hash()] = toString(moves);
        }
    } else {
        traversedWithLength[board.hash()] = toString(moves);
    }
    vector<string> subsets = vector<string>();
    if (board.isASolution()) {
        cout << toString(moves) << endl;
        finished = true;
    } else {
        if (!finished) {
            subsets = constructCandidates(board);
            for (int i = 0; i < subsets.size(); i++) {
                moves.push_back(subsets.at(i));
                Board boardClone = board.clone();
                board = move(board, subsets.at(i));
                backtrack(board, moves, maxPoint);
                moves.pop_back();
                board = boardClone.clone();
            }
        }
    }
}

int main() {
    fstream file;
    file.open("Puzzle.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int times;
        file >> times;
        for (int i = 0; i < times; i++) {
            Board board = Board(file);
            traversedWithLength = unordered_map<long, string>();
            finished = false;
            cout << board.point() << endl;
            backtrack(board, vector<string>(), board.point());
            if (!finished) {
                cout << "No Solution" << endl;
            }
        }
    }
}