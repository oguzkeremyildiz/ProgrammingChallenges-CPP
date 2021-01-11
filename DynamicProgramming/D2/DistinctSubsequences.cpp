//
// Created by Oğuz Kerem Yıldız on 11.01.2021.
//
#include <fstream>
#include <iostream>

using namespace std;

void find(const string& first, const string& second) {
    long long int **dp;
    dp = (long long int **)malloc(first.length() * sizeof(long long int *));
    for (int i = 0; i < first.length(); i++) {
        dp[i] = (long long int *) malloc(second.length() * sizeof(long long int));
    }
    for (int i = 0; i < first.length(); i++) {
        for (int j = 0; j < second.length(); j++) {
            dp[i][j] = 0;
        }
    }
    for (int i = 0; i < first.length(); i++) {
        for (int j = 0; j < second.length(); j++) {
            if (first.at(i) == second.at(j)) {
                if (j > 0) {
                    if (i > 0) {
                        dp[i][j] += dp[i - 1][j - 1];
                        dp[i][j] += dp[i - 1][j];
                    } else {
                        dp[i][j] = 0;
                    }
                } else {
                    if (i > 0) {
                        dp[i][j] = dp[i - 1][j];
                    }
                    dp[i][j] += 1;
                }
            } else {
                if (i > 0) {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
    }
    cout << dp[first.length() - 1][second.length() - 1] << endl;
}

int main() {
    fstream file;
    file.open("Sequence.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int times;
        file >> times;
        for (int i = 0; i < times; i++) {
            string first, second;
            file >> first;
            file >> second;
            find(first, second);
        }
    }
}