//
// Created by Oğuz Kerem Yıldız on 3.01.2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

int hartals(int days, vector<int> numbers) {
    unordered_set<int> number = unordered_set<int>();
    for (int integer : numbers) {
        for (int j = 1; j <= days; j++) {
            if (j % 7 != 0 && j % 7 != 6) {
                if (j % integer == 0) {
                    number.insert(j);
                }
            }
        }
    }
    return number.size();
}

int main() {
    fstream file;
    file.open("Hartals.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int times, days, party, day;
        vector<int> numbers = vector<int>();
        file >> times;
        for (int i = 0; i < times; i++) {
            file >> days;
            file >> party;
            for (int j = 0; j < party; j++) {
                file >> day;
                numbers.push_back(day);
            }
            cout << hartals(days, numbers) << endl;
            numbers.clear();
        }
    }
}