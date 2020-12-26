//
// Created by Oğuz Kerem Yıldız on 27.12.2020.
//

#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

static int total;

bool isASolution(int left, int right, vector<int> sequence) {
    bool boolean = false;
    int checkLeft = 0;
    int checkRight = 0;
    bool isLeft;
    bool isRight;
    for (int i = 0; i < sequence.size(); i++) {
        isLeft = true;
        isRight = true;
        for (int j = 0; j < sequence.size(); j++) {
            if (i != j) {
                if (i < j) {
                    if (sequence.at(i) < sequence.at(j)) {
                        isRight = false;
                        break;
                    }
                } else {
                    if (sequence.at(i) < sequence.at(j)) {
                        isLeft = false;
                        j = i;
                    }
                }
            }
        }
        if (isLeft) {
            checkLeft++;
        }
        if (isRight) {
            checkRight++;
        }
    }
    if (checkLeft == left) {
        if (checkRight == right) {
            boolean = true;
        }
    }
    return boolean;
}

vector<int> constructCandidates(int people, vector<int> sequence) {
    vector<int> subsets = vector<int>();
    unordered_set<int> set = unordered_set<int>();
    for (int integer : sequence) {
        set.insert(integer);
    }
    for (int i = 1; i <= people; i++) {
        if (set.find(i) == set.end()) {
            subsets.push_back(i);
        }
    }
    return subsets;
}

void backtrack(int people, int left, int right, vector<int> sequence) {
    vector<int> subsets;
    if (sequence.size() == people) {
        if (isASolution(left, right, sequence)) {
            total++;
        }
    } else {
        subsets = constructCandidates(people, sequence);
        for (int i = 0; i < subsets.size(); i++) {
            sequence.push_back(subsets.at(i));
            backtrack(people, left, right, sequence);
            sequence.pop_back();
        }
    }
}

int main() {
    fstream file;
    file.open("Queue.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int times, people, left, right;
        file >> times;
        for (int i = 0; i < times; i++) {
            total = 0;
            file >> people;
            file >> left;
            file >> right;
            backtrack(people, left, right, vector<int>());
            cout << total << endl;
        }
    }
}