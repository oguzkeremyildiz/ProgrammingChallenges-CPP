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

vector<int> flip(vector<int> pancakes, int index) {
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
    return pancakes;
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

vector<int> find(vector<int> pancakes, int i) {
    vector<int> results = vector<int>();
    int tmp = 0;
    int element;
    vector<int> realPancakes = vector<int>(pancakes);
    Comparator<int> *comparator = new IntegerComparator();
    QuickSort<int> quickSort = QuickSort<int>(comparator);
    realPancakes = quickSort.sort(realPancakes, 0, realPancakes.size() - 1);
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
        pancakes = flip(pancakes, tmp);
        pancakes = flip(pancakes, pancakes.size() - 1 - i);
        results.push_back(1 + i);
    }
    i++;
    if (i < pancakes.size()) {
        if (realPancakes != pancakes) {
            vector<int> current = find(pancakes, i);
            for (int j = 0; j < current.size(); j++) {
                results.push_back(current.at(j));
            }
        } else {
            results.push_back(0);
            print(pancakes);
        }
    }
    return results;
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
            results = find(pancakes, 0);
            for (int result : results) {
                cout << to_string(result) + " ";
            }
            cout << "" << endl;
        }
    }
}