//
// Created by Oğuz Kerem Yıldız on 16.01.2021.
//
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int number, numberT, temporary;
    cin >> number;
    numberT = number;
    vector<int> digitReverse = vector<int>();
    while (number != 0) {
        temporary = number % 10;
        number = (number - temporary) / 10;
        digitReverse.push_back(temporary);
    }
    int numberTReverse = 0;

    for (int i = 0; i < digitReverse.size(); i++) {
        numberTReverse += digitReverse.at(digitReverse.size() - i - 1) * pow(10, i);
    }
    int output = numberT + numberTReverse;
    cout << "total: " + to_string(output) << endl;
}