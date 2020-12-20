//
// Created by Oğuz Kerem Yıldız on 20.12.2020.
//
#include "Number.h"
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

class Hash {
public:
    size_t operator()(const Number& p) const
    {
        return p.x * p.y * p.value;
    }
};

void fillMatrix(Number **numbers, Number **dp, int x, int y, unordered_map<Number, Number, Hash>* map, int size) {
    Number bestValue = Number(-1, -1, INT_MAX);
    if (bestValue.value > dp[x][y - 1].value) {
        bestValue = dp[x][y - 1];
    }
    if (x + 1 < size) {
        if (bestValue.value > dp[x + 1][y - 1].value) {
            bestValue = dp[x + 1][y - 1];
        }
    } else {
        if (bestValue.value > dp[0][y - 1].value) {
            bestValue = dp[0][y - 1];
        }
    }
    if (x - 1 > -1) {
        if (bestValue.value > dp[x - 1][y - 1].value) {
            bestValue = dp[x - 1][y - 1];
        }
    } else {
        if (bestValue.value > dp[size - 1][y - 1].value) {
            bestValue = dp[size - 1][y - 1];
        }
    }
    dp[x][y] = Number(x, y, bestValue.value + numbers[x][y].value);
    (*map)[numbers[x][y]] = numbers[bestValue.x][bestValue.y];
}

void findBestPath(Number **numbers, int size1, int size2) {
    unordered_map<Number, Number, Hash> map;
    Number **dp;
    dp = (Number **)malloc(size1 * sizeof(Number *));
    for (int i = 0; i < sizeof(dp); i++) {
        dp[i] = (Number *)malloc(size2 * sizeof(Number));
    }
    for (int i = 0; i < size1; i++) {
        dp[i][0] = numbers[i][0];
    }
    for (int i = 1; i < size2; i++) {
        for (int j = 0; j < size1; j++) {
            fillMatrix(numbers, dp, j, i, &map, size1);
        }
    }
    Number best = Number(-1, -1, INT_MAX);
    int bestValue = INT_MAX;
    for (int i = 0; i < size1; i++) {
        Number *ints = dp[i];
        if (bestValue > ints[size2 - 1].value) {
            bestValue = ints[size2 - 1].value;
            best = numbers[i][size2 - 1];
        }
    }
    Number *current = &best;
    printf("%i", current->x + 1);
    do {
        if (map.find(*current) != map.end()) {
            printf("%s%i", " ", (map[*current].x + 1));
            *current = map[*current];
        } else {
            current = nullptr;
        }
    } while (current != nullptr);
    cout << "" << endl;
    cout << bestValue << endl;
}

int main() {
    fstream file;
    file.open("Unidirectional.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        while (!file.eof()) {
            int size1, size2;
            file >> size1;
            file >> size2;
            Number **numbers;
            numbers = (Number **)malloc(size1 * sizeof(Number *));
            for (int i = 0; i < sizeof(numbers); i++) {
                numbers[i] = (Number *)malloc(size2 * sizeof(Number));
            }
            for (int i = 0; i < size1; i++) {
                for (int j = 0; j < size2; j++) {
                    int value;
                    file >> value;
                    numbers[i][j] = Number(i, j, value);
                }
            }
            findBestPath(numbers, size1, size2);
        }
    }
}