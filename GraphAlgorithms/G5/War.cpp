//
// Created by Oğuz Kerem Yıldız on 1.02.2021.
//
#include <iostream>
#include "Disjoint.h"
#include <fstream>
#include <vector>

using namespace std;

void setDisjoint(Disjoint<int> &set, int command, int nodeOne, int nodeTwo) {
    switch (command) {
        case 1:
            if (set.isEnemy(nodeOne, nodeTwo)) {
                cout << "-1" << endl;
            } else {
                if (set.findSetWithIndex(nodeOne) != set.findSetWithIndex(nodeTwo)) {
                    set.unionWithType(nodeOne, nodeTwo);
                }
            }
            break;
        case 2:
            if (set.findSetWithIndex(nodeOne) == set.findSetWithIndex(nodeTwo)) {
                cout << "-1" << endl;
            } else {
                if (!set.isEnemy(nodeOne, nodeTwo)){
                    set.setEnemies(nodeOne, nodeTwo);
                }
            }
            break;
        case 3:
            if (set.findSetWithIndex(nodeOne) == set.findSetWithIndex(nodeTwo)) {
                cout << "1" << endl;
            } else {
                cout << "0" << endl;
            }
            break;
        case 4:
            if (set.isEnemy(nodeOne, nodeTwo)) {
                cout << "1" << endl;
            } else {
                cout << "0" << endl;
            }
            break;
        default:
            break;
    }
}

int main() {
    fstream file;
    file.open("Friend.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int size;
        file >> size;
        vector<int> elements = vector<int>();
        for (int i = 0; i < size; ++i) {
            elements.push_back(i);
        }
        Disjoint<int> set = Disjoint<int>(elements);
        while (!file.eof()) {
            int command, nodeOne, nodeTwo;
            file >> command;
            file >> nodeOne;
            file >> nodeTwo;
            if (command == 0 && nodeOne == 0 && nodeTwo == 0) {
                break;
            } else {
                setDisjoint(set, command, nodeOne, nodeTwo);
            }
        }
    }
}