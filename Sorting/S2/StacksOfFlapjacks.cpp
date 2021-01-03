//
// Created by Oğuz Kerem Yıldız on 3.01.2021.
//

#include <fstream>
#include <iostream>
#include <vector>
#include "Sort/QuickSort.h"
#include <sstream>

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

void flip(vector<int> &pancakes, int index) {
    int tmp;
    int checkFirst;
    int checkSecond;
    if (pancakes.size() > index){
        for (int i = 0; i < index; i++) {
            checkFirst = i;
            checkSecond = index - i;
            if (checkSecond > checkFirst) {
                tmp = pancakes.at(i);
                pancakes.at(i) = pancakes.at(index - i);
                pancakes.at(index - i) = tmp;
            } else {
                break;
            }
        }
    }
}

void print(vector<int> pancakes) {
    cout << "[";
    for (int i = 0; i < pancakes.size(); i++) {
        if (i + 1 == pancakes.size()) {
            cout << pancakes.at(i);
        } else {
            cout << to_string(pancakes.at(i)) + ", ";
        }
    }
    cout << "]";
    cout << "" << endl;
}

void find(vector<int> &pancakes, int i, vector<int> &results) {
    int tmp = 0;
    int element;
    vector<int> realPancakes = vector<int>(pancakes);
    Comparator<int> *comparator = new IntegerComparator();
    QuickSort<int> quickSort = QuickSort<int>(comparator);
    quickSort.sort(realPancakes, 0, realPancakes.size() - 1);
    if (pancakes.at(0) != realPancakes.at(realPancakes.size() - 1 - i)) {
        element = realPancakes.at(realPancakes.size() - 1 - i);
    } else {
        element = pancakes.at(0);
    }
    if (pancakes.at(pancakes.size() - 1 - i) != element) {
        for (int j = 0; j < pancakes.size(); j++) {
            if (pancakes.at(j) == element) {
                tmp = j;
                break;
            }
        }
        flip(pancakes, tmp);
        flip(pancakes, pancakes.size() - 1 - i);
        results.push_back(1 + i);
    }
    i++;
    if (i < pancakes.size()) {
        if (realPancakes != pancakes) {
            find(pancakes, i, results);
        } else {
            results.push_back(0);
            print(pancakes);
        }
    }
}

int main() {
    fstream file;
    file.open("Pancakes.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        string line;
        int pancake;
        vector<string> split;
        vector<int> pancakes = vector<int>();
        vector<int> results = vector<int>();
        while (!file.eof()) {
            pancakes.clear();
            results.clear();
            split.clear();
            getline(file, line);
            stringstream check(line);
            string intermediate;
            while (getline(check, intermediate, ' ')) {
                split.push_back(intermediate);
            }
            for (string s : split) {
                pancake = stoi(s);
                pancakes.push_back(pancake);
            }
            find(pancakes, 0, results);
            for (int result : results) {
                cout << to_string(result) + " ";
            }
            cout << "" << endl;
        }
    }
}