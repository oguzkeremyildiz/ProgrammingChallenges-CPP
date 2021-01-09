//
// Created by Oğuz Kerem Yıldız on 10.01.2021.
//
#include <iostream>
#include <unordered_set>
#include <vector>
#include <fstream>

using namespace std;

void print(unordered_set<string> elements, vector<string> sortedList) {
    for (int i = 0; i < sortedList.size(); i++) {
        if (elements.find(sortedList.at(sortedList.size() - 1 - i)) != elements.end()) {
            cout << sortedList.at(sortedList.size() - 1 - i) << endl;
        }
    }
}

void swapToFirst(int index, vector<string> &turtles) {
    string turtle = turtles.at(index);
    turtles.erase(turtles.begin() + index);
    turtles.insert(turtles.begin(), turtle);
}

void editList(vector<string> &turtle, vector<string> &sortedTurtle) {
    unordered_set<string> elements = unordered_set<string>();
    while (turtle != sortedTurtle) {
        for (int i = 0; i < turtle.size(); i++) {
            if (turtle.at(turtle.size() - 1 - i) != sortedTurtle.at(sortedTurtle.size() - 1 - i)) {
                elements.insert(turtle.at(turtle.size() - 1 - i));
                swapToFirst(turtle.size() - 1 - i, turtle);
                break;
            }
        }
    }
    if (turtle == sortedTurtle) {
        print(elements, sortedTurtle);
    }
}

int main() {
    fstream file;
    file.open("Turtles.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        vector<string> turtle = vector<string>();
        vector<string> sortedTurtle = vector<string>();
        string timesString, turtlesString;
        getline(file, timesString);
        int times = stoi(timesString);
        string line;
        for (int i = 0; i < times; i++) {
            turtle.clear();
            sortedTurtle.clear();
            getline(file, turtlesString);
            int turtles = stoi(turtlesString);
            for (int j = 0; j < turtles * 2; j++) {
                getline(file, line);
                if (j > turtles - 1) {
                    sortedTurtle.push_back(line);
                } else {
                    turtle.push_back(line);
                }
            }
            editList(turtle, sortedTurtle);
            cout << "" << endl;
        }
    }
}