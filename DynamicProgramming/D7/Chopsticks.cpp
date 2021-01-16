//
// Created by Oğuz Kerem Yıldız on 15.01.2021.
//
#include <iostream>
#include "Chopstick.h"
#include <unordered_map>
#include <fstream>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

bool isThereAChopstick(int *array, int currentIndex, int arrayLength) {
    array[currentIndex + 1] = -1;
    for (int i = currentIndex; i < arrayLength; i++) {
        if (array[i] == 0) {
            array[i] = -1;
            return true;
        }
    }
    return false;
}

bool suitable(const bool *visited, Chopstick &chopstick1, Chopstick &chopstick2, int visitedLength) {
    if (!visited[chopstick1.getIndex()] && !visited[chopstick2.getIndex()]) {
        int *array = (int *)calloc(visitedLength, sizeof(int));
        for (int i = 0; i < visitedLength; i++) {
            if (visited[i] || chopstick1.getIndex() == i || chopstick2.getIndex() == i) {
                array[i] = 1;
            }
        }
        for (int i = 0; i < visitedLength; i++) {
            if (array[i] == 1) {
                if (!isThereAChopstick(array, i, visitedLength)) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

int findBadness(int **dp, Chopstick *chopstick, int length1, int length2) {
    int badness = 0;
    unordered_map<int, vector<Chopstick>> map = unordered_map<int, vector<Chopstick>>();
    for (int i = 0; i < length2; i++) {
        if (dp[length1 - 1][i] != 0) {
            map[dp[length1 - 1][i]].push_back(chopstick[i]);
        }
    }
    for (auto &key : map) {
        badness += pow(abs(map[key.first].at(0).getChopstick() - map[key.first].at(1).getChopstick()), 2);
    }
    return badness;
}

pair<Chopstick, Chopstick> findPair(vector<Chopstick> &list, Chopstick &current, Chopstick &first, Chopstick &second, bool *visited, int visitedLength) {
    list.push_back(current);
    if (list.size() > 1) {
        Chopstick returning1 = first;
        Chopstick returning2 = second;
        for (int i = 0; i < list.size() - 1; i++) {
            if (abs(returning1.getChopstick() - returning2.getChopstick()) > abs(current.getChopstick() - list.at(i).getChopstick()) && suitable(visited, current, list.at(i), visitedLength)) {
                returning1 = current;
                returning2 = list.at(i);
            }
        }
        return {returning1, returning2};
    }
    return {Chopstick(INT_MAX, INT_MAX), Chopstick(INT_MAX, INT_MAX)};
}

void fill(int **dp, Chopstick &first, Chopstick &second, int i, Chopstick *chopstick, int length2) {
    if (i - 1 > -1) {
        for (int j = 0; j < length2; ++j) {
            dp[i][j] = dp[i - 1][j];
        }
    }
    if (abs(first.getIndex() - second.getIndex()) != 1) {
        if (first.getIndex() > second.getIndex()) {
            int index = dp[i][first.getIndex() - 1];
            int compare1 = chopstick[first.getIndex() - 1].getChopstick();
            int compare2 = chopstick[second.getIndex() + 1].getChopstick();
            if (pow(first.getChopstick() - compare1, 2) + pow(compare2 - second.getChopstick(), 2) < pow(compare1 - compare2, 2) + pow(first.getChopstick() - second.getChopstick(), 2)) {
                dp[i][first.getIndex()] = i + 1;
                dp[i][first.getIndex() - 1] = i + 1;
                dp[i][second.getIndex()] = index;
                dp[i][second.getIndex() + 1] = index;
            } else {
                dp[i][first.getIndex()] = i + 1;
                dp[i][second.getIndex()] = i + 1;
            }
        } else {
            int index = dp[i][second.getIndex() - 1];
            int compare1 = chopstick[second.getIndex() - 1].getChopstick();
            int compare2 = chopstick[first.getIndex() + 1].getChopstick();
            if (pow(second.getChopstick() - compare1, 2) + pow(compare2 - first.getChopstick(), 2) < pow(compare1 - compare2, 2) + pow(second.getChopstick() - first.getChopstick(), 2)) {
                dp[i][second.getIndex()] = i + 1;
                dp[i][second.getIndex() - 1] = i + 1;
                dp[i][first.getIndex()] = index;
                dp[i][first.getIndex() + 1] = index;
            } else {
                dp[i][second.getIndex()] = i + 1;
                dp[i][first.getIndex()] = i + 1;
            }
        }
    } else {
        dp[i][first.getIndex()] = i + 1;
        dp[i][second.getIndex()] = i + 1;
    }
}

int find(Chopstick *chopstick, int people, int length) {
    int **dp;
    dp = (int **)calloc(people, sizeof(int *));
    for (int i = 0; i < people; ++i) {
        dp[i] = (int*) calloc(length, sizeof(int));
    }
    bool *visited = (bool *)calloc(length, sizeof(bool));
    for (int i = 0; i < people; i++) {
        vector<Chopstick> list = vector<Chopstick>();
        Chopstick first = Chopstick(-1, INT_MAX);
        Chopstick second = Chopstick(-1, 0);
        for (int j = 0; j < length; j++) {
            pair<Chopstick, Chopstick> pair = findPair(list, chopstick[j], first, second, visited, length);
            if (!(pair.first.getIndex() == INT_MAX && pair.first.getChopstick() == INT_MAX && pair.second.getIndex() == INT_MAX && pair.second.getChopstick() == INT_MAX)) {
                first = pair.first;
                second = pair.second;
            }
        }
        fill(dp, first, second, i, chopstick, length);
        visited[first.getIndex()] = true;
        visited[second.getIndex()] = true;
    }
    return findBadness(dp, chopstick, people, length);
}

int main() {
    fstream file;
    file.open("Chopstick.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int times, people, chopsticks, element;
        file >> times;
        for (int i = 0; i < times; i++) {
            file >> people;
            file >> chopsticks;
            auto *chopstick = new Chopstick[chopsticks];
            for (int j = 0; j < chopsticks; j++) {
                file >> element;
                chopstick[j] = Chopstick(j, element);
            }
            cout << find(chopstick, people + 8, chopsticks) << endl;
        }
    }
}