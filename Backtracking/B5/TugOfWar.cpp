//
// Created by Oğuz Kerem Yıldız on 16.01.2021.
//
#include <fstream>
#include <iostream>
#include <vector>
#include "Sort/QuickSort.h"
#include "Comparator.h"
#include <utility>
#include <cmath>

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

static bool finished;
static int smallest, bestDifference;
static pair<vector<int>, vector<int>> p = pair<vector<int>, vector<int>>(vector<int>(), vector<int>());

void print() {
    int totalKey = 0;
    int totalValue = 0;
    for (int i : p.first) {
        totalKey += i;
    }
    for (int i : p.second) {
        totalValue += i;
    }
    cout << to_string(totalKey) + " " + to_string(totalValue) << endl;
}

void smallestDifference(vector<int> persons) {
    int total = 0;
    for (int i = 0; i < persons.size(); ++i) {
        total += persons.at(i);
    }
    if (total % 2 == 0){
        smallest = 0;
    } else {
        smallest = 1;
    }
}

int difference(pair<vector<int>, vector<int>> pair) {
    int totalKey = 0, totalValue = 0;
    for (int i : pair.first) {
        totalKey += i;
    }
    for (int i : pair.second) {
        totalValue += i;
    }
    return abs(totalKey - totalValue);
}

pair<bool, pair<vector<int>, vector<int>>> isASolution(vector<int> sequence, vector<int> persons) {
    pair<vector<int>, vector<int>> returning = pair<vector<int>, vector<int>>(vector<int>(), vector<int>());
    bool boolean;
    boolean = p.second.empty() && p.first.empty();
    for (int i = 0; i < sequence.size(); i++) {
        if (sequence.at(i) == 0) {
            returning.first.push_back(persons.at(i));
        } else {
            returning.second.push_back(persons.at(i));
        }
    }
    if (!boolean) {
        if (difference(returning) < bestDifference) {
            bestDifference = difference(returning);
            boolean = true;
        }
    }
    return pair<bool, pair<vector<int>, vector<int>>>(boolean, returning);
}

void constructCandidates(vector<int> persons, vector<int> sequence, vector<int> &subsets) {
    int sum1 = 0, sum2 = 0, sumRemaining = 0;
    for (int i = 0; i < sequence.size(); i++) {
        if (sequence.at(i) == 0) {
            sum1 += persons.at(i);
        } else {
            sum2 += persons.at(i);
        }
    }
    for (int j = sequence.size(); j < persons.size(); j++){
        sumRemaining += persons.at(j);
    }
    if (min(sum1, sum2) + sumRemaining < max(sum1, sum2)){
        return;
    }
    subsets.push_back(1);
    subsets.push_back(0);
}

void backtrack(vector<int> &persons, vector<int> sequence) {
    if (bestDifference <= smallest && !p.first.empty() && !p.second.empty()) {
        return;
    }
    vector<int> subsets = vector<int>();
    if (sequence.size() == persons.size()) {
        if (isASolution(sequence, persons).first) {
            p = isASolution(sequence, persons).second;
        }
        finished = true;
    } else {
        if (!finished){
            constructCandidates(persons, sequence, subsets);
            for (int subset : subsets) {
                sequence.push_back(subset);
                backtrack(persons, sequence);
                sequence.pop_back();
                finished = false;
            }
        }
    }
}

string toString(vector<int> vec) {
    string s = "[";
    for (int i = 0; i < vec.size(); ++i) {
        if (vec.size() - 1 == i) {
            s += to_string(vec.at(i));
        } else {
            s += to_string(vec.at(i)) + ", ";
        }
    }
    s += "]";
    return s;
}

int main() {
    fstream file;
    file.open("War.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int times, person, next;
        file >> times;
        file >> person;
        vector<int> persons = vector<int>();
        for (int i = 0; i < times; i++) {
            finished = false;
            for (int j = 0; j < person; j++) {
                file >> next;
                persons.push_back(next);
            }
            Comparator<int> *comparator = new IntegerComparator();
            QuickSort<int> quickSort = QuickSort<int>(comparator);
            quickSort.sort(persons, 0, persons.size() - 1);
            smallestDifference(persons);
            bestDifference = 1000;
            backtrack(persons, vector<int>());
            cout << toString(p.first) + " " + toString(p.second) << endl;
            print();
        }
    }
}