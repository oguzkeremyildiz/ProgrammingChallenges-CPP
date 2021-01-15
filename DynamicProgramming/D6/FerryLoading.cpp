//
// Created by Oğuz Kerem Yıldız on 13.01.2021.
//
#include <fstream>
#include <iostream>
#include <vector>
#include "Node.h"


using namespace std;

void setChosen(vector<Node> &chosen, unsigned long long int **dp, int i, int j, vector<Node> list) {
    if (i > 0 && j - list.at(i).getWeight() > -1 && dp[i - 1][j - list.at(i).getWeight()] + list.at(i).getValue() > dp[i - 1][j]) {
        chosen.push_back(list.at(i));
        if (i > 0) {
            setChosen(chosen, dp, i - 1, j - list.at(i).getWeight(), list);
        }
    } else {
        if (i > 0) {
            setChosen(chosen, dp, i - 1, j, list);
        }
    }
}

bool control(vector<Node> list, int i, int j, unsigned long long int **dp, int ferry) {
    vector<Node> chosen = vector<Node>();
    setChosen(chosen, dp, i, j, list);
    int total1 = 0, total2 = 0;
    for (int k = 0; k < i + 1; ++k) {
        if (find(chosen.begin(), chosen.end(), list.at(k)) != chosen.end()) {
            total1 += list.at(k).getWeight();
        } else {
            total2 += list.at(k).getWeight();
        }
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
    for (int i = 0; i < list.size(); ++i) {
        if (find(port.begin(), port.end(), list.at(i)) == port.end()) {
            if (total + list.at(i).getWeight() > ferry) {
                break;
            }
            total += list.at(i).getWeight();
            starboard.push_back(list.at(i));
        }
    }
    cout << port.size() + starboard.size() << endl;
    for (int i = 0; i < list.size(); ++i) {
        if (find(port.begin(), port.end(), list.at(i)) != port.end()) {
            cout << "port" << endl;
        } else if (find(starboard.begin(), starboard.end(), list.at(i)) != starboard.end()) {
            cout << "starboard" << endl;
        }
    }
}

void dp(vector<Node> list, int ferry) {
    unsigned long long int **dp;
    dp = (unsigned long long int **)malloc(list.size() * sizeof(unsigned long long int *));
    for (int i = 0; i < list.size(); ++i) {
        dp[i] = (unsigned long long int *) malloc((ferry + 1) * sizeof(unsigned long long int));
    }
    for (int i = 0; i < list.size(); ++i) {
        for (int j = 0; j < ferry + 1; ++j) {
            dp[i][j] = 0;
        }
    }
    for (int i = 0; i < ferry + 1; i++) {
        if (i >= list.at(0).getWeight()) {
            dp[0][i] = list.at(0).getValue();
        }
    }
    for (int i = 1; i < list.size(); ++i) {
        if (list.at(i).getWeight() < ferry + 1) {
            for (int j = 1; j < ferry + 1; ++j) {
                if (j - list.at(i).getWeight() > -1 && dp[i - 1][j - list.at(i).getWeight()] + list.at(i).getValue() > dp[i - 1][j] && control(list, i, j, dp, ferry)) {
                    dp[i][j] = dp[i - 1][j - list.at(i).getWeight()] + list.at(i).getValue();
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
    }
    print(dp, ferry, list);
}

unsigned long long int pow(unsigned long long int first, int second) {
    unsigned long long int total = first;
    for (int i = 1; i < second; ++i) {
        total *= first;
    }
    return total;
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
            while (current != 0) {
                file >> current;
                if (current != 0) {
                    index++;
                    unsigned long long int value = pow(10, index);
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