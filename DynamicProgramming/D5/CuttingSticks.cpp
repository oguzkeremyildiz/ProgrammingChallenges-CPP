//
// Created by Oğuz Kerem Yıldız on 4.01.2021.
//
#include <iostream>
#include <fstream>
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

int calculateDp(int i, int j, int **dp, int *array) {
    if (dp[i][j] < 0){
        int min = INT_MAX;
        for (int k = i + 1; k < j; k++) {
            min = std::__1::min(min, calculateDp(i, k, dp, array) + calculateDp(k, j, dp, array));
        }
        dp[i][j] = min + array[j] - array[i];
    }
    return dp[i][j];
}

int find(int *array, int length) {
    Comparator<int> *comparator = new IntegerComparator();
    QuickSort<int> quickSort = QuickSort<int>(comparator);
    quickSort.sort(array, 0, length - 1);
    int **dp;
    dp = (int **)malloc(length * sizeof(int *));
    for (int i = 0; i < length; i++) {
        dp[i] = (int*) malloc(length * sizeof(int));
    }
    for (int i = 0; i < length - 1; i++) {
        dp[i][i + 1] = 0;
        for (int j = i + 2; j < length; j++) {
            dp[i][j] = -1;
        }
    }
    for (int i = 0; i < length; i++){
        for (int j = i + 2; j < length; j++) {
            calculateDp(i, j, dp, array);
        }
    }
    return dp[0][length - 1];
}

int main() {
    fstream file;
    file.open("Sticks.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        while (!file.eof()) {
            int totalMeter, times;
            file >> totalMeter;
            if (totalMeter > 0) {
                file >> times;
                int *array = new int[times + 2];
                array[0] = 0;
                for (int i = 0; i < times; i++) {
                    file >> array[i];
                }
                array[times] = totalMeter;
                cout << "The minimum cutting is " + to_string(find(array, times + 2)) + "." << endl;
            }
        }
    }
}