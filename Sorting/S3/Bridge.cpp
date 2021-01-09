//
// Created by Oğuz Kerem Yıldız on 9.01.2021.
//
#include <fstream>
#include <iostream>
#include <vector>
#include "Sort/QuickSort.h"

using namespace std;

class IntegerComparator : public Comparator<int> {
public:
    IntegerComparator() = default;
    virtual int compare(int first, int second) {
        if (first > second) {
            return 1;
        } else if (first < second) {
            return -1;
        } else {
            return 0;
        }
    }
};

int bridge(vector<int> start, vector<int> finish) {
    Comparator<int> *comparator = new IntegerComparator();
    QuickSort<int> quickSort = QuickSort<int>(comparator);
    int index = 0;
    int sum = 0;
    if (start.size() % 2 == 0) {
        sum += start.at(1);
        cout << to_string(start.at(0)) + " " + to_string(start.at(1));
        finish.push_back(start.at(0));
        finish.push_back(start.at(1));
    } else {
        sum += start.at(0);
        sum += start.at(1);
        sum += start.at(2);
        cout << to_string(start.at(0)) + " " + to_string(start.at(1));
        cout << "" << endl;
        cout << start.at(0);
        cout << "" << endl;
        cout << to_string(start.at(0)) + " " + to_string(start.at(2));
        finish.push_back(start.at(0));
        finish.push_back(start.at(1));
        finish.push_back(start.at(2));
    }
    while (finish.size() != start.size()) {
        sum += finish.at(0);
        cout << "" << endl;
        cout << finish.at(0);
        finish.erase(finish.begin() + 0);
        sum += start.at(start.size() - 1 - index);
        finish.push_back(start.at(start.size() - 1 - index));
        finish.push_back(start.at(start.size() - 2 - index));
        cout << "" << endl;
        cout << to_string(start.at(start.size() - 2 - index)) + " " + to_string(start.at(start.size() - 1 - index));
        sum += finish.at(0);
        cout << "" << endl;
        cout << finish.at(0);
        cout << "" << endl;
        cout << to_string(start.at(0)) + " " + to_string(finish.at(0));
        sum += finish.at(0);
        finish.push_back(start.at(0));
        index += 2;
        quickSort.sort(finish, 0, finish.size() - 1);
    }
    cout << "" << endl;
    return sum;
}

int main() {
    fstream file;
    file.open("Bridge.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int timesOne, timesSecond, lines;
        file >> timesOne;
        vector<int> start = vector<int>();
        vector<int> finish = vector<int>();
        for (int i = 0; i < timesOne; i++){
            file >> timesSecond;
            start.clear();
            finish.clear();
            for (int j = 0; j < timesSecond; j++) {
                file >> lines;
                start.push_back(lines);
            }
            cout << bridge(start, finish) << endl;
        }
    }
}