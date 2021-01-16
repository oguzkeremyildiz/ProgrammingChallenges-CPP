//
// Created by Oğuz Kerem Yıldız on 13.01.2021.
//
#include <fstream>
#include <iostream>
#include <vector>
#include "Node.h"


using namespace std;

bool control(vector<Node> list, unsigned long long int current, int ferry) {
    vector<Node> port = vector<Node>();
    vector<Node> starboard = vector<Node>();
    int endIndex = INT_MAX;
    for (int n = list.size() - 1; n > -1; n--) {
        if (list.at(n).getValue() <= current) {
            if (endIndex == INT_MAX) {
                endIndex = n;
            }
            current -= list.at(n).getValue();
            port.push_back(list.at(n));
        }
    }
    for (int n = 0; n < endIndex; ++n) {
        if (find(port.begin(), port.end(), list.at(n)) == port.end()) {
            starboard.push_back(list.at(n));
        }
    }
    int total1 = 0, total2 = 0;
    for (auto & k : port) {
        total1 += k.getWeight();
    }
    for (auto & k : starboard) {
        total2 += k.getWeight();
    }
    return ferry >= total1 && ferry >= total2;
}

void print(unsigned long long int **dp, int ferry, vector<Node> list) {
    vector<Node> port = vector<Node>();
    vector<Node> starboard = vector<Node>();
    unsigned long long int totalScore = dp[list.size() - 1][ferry];
    for (int i = list.size() - 1; i > -1; i--) {
        if (list.at(i).getValue() <= totalScore) {
            totalScore -= list.at(i).getValue();
            port.push_back(list.at(i));
        }
    }
    int total = 0;
    for (auto & i : list) {
        if (find(port.begin(), port.end(), i) == port.end()) {
            if (total + i.getWeight() > ferry) {
                break;
            }
            total += i.getWeight();
            starboard.push_back(i);
        }
    }
    cout << port.size() + starboard.size() << endl;
    for (auto & i : list) {
        if (find(port.begin(), port.end(), i) != port.end()) {
            cout << "port" << endl;
        } else if (find(starboard.begin(), starboard.end(), i) != starboard.end()) {
            cout << "starboard" << endl;
        }
    }
}

void dp(vector<Node> list, int ferry) {
    unsigned long long int **dp;
    dp = (unsigned long long int **)calloc(list.size(), sizeof(unsigned long long int *));
    for (int i = 0; i < list.size(); ++i) {
        dp[i] = (unsigned long long int *) calloc((ferry + 1), sizeof(unsigned long long int));
    }
    for (int i = 0; i < ferry + 1; i++) {
        if (i >= list.at(0).getWeight()) {
            dp[0][i] = list.at(0).getValue();
        }
    }
    for (int i = 1; i < list.size(); ++i) {
        if (list.at(i).getWeight() < ferry + 1) {
            for (int j = 1; j < ferry + 1; ++j) {
                if (j - list.at(i).getWeight() > -1 && dp[i - 1][j - list.at(i).getWeight()] + list.at(i).getValue() > dp[i - 1][j] && control(list, dp[i - 1][j - list.at(i).getWeight()] + list.at(i).getValue(), ferry)) {
                    dp[i][j] = dp[i - 1][j - list.at(i).getWeight()] + list.at(i).getValue();
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
    }
    print(dp, ferry, list);
}

unsigned long long int setValues(vector<unsigned long long int> &values) {
    if (values.empty()) {
        values.push_back(1);
    } else {
        unsigned long long int total = 1;
        for (unsigned long long value : values) {
            total += value;
        }
        values.push_back(total);
    }
    return values.at(values.size() - 1);
}

int main() {
    fstream file;
    file.open("Ferry.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        vector<Node> list = vector<Node>();
        int times, ferry, index;
        file >> times;
        for (int i = 0; i < times; i++) {
            index = 0;
            file >> ferry;
            int current = INT_MAX;
            vector<unsigned long long int> values = vector<unsigned long long int>();
            while (current != 0) {
                file >> current;
                if (current != 0) {
                    index++;
                    unsigned long long int value = setValues(values);
                    list.emplace_back(value, current);
                }
            }
            if (list.at(0).getWeight() <= ferry * 100) {
                dp(list, ferry * 100);
            } else {
                cout << "0" << endl;
            }
            cout << "" << endl;
            list.clear();
        }
    }
}