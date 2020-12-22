//
// Created by Oğuz Kerem Yıldız on 22.12.2020.
//

#include <unordered_set>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

bool jollyCount(vector<int> numbers) {
    unordered_set<int> count;
    for (int i = 0; i < numbers.size() - 1; i++) {
        if (numbers.at(i) < numbers.at(i + 1)) {
            if (numbers.at(i + 1) - numbers.at(i) < numbers.size() && numbers.at(i + 1) - numbers.at(i) != 0) {
                if (count.find(numbers.at(i + 1) - numbers.at(i)) == count.end()) {
                    count.insert(numbers.at(i + 1) - numbers.at(i));
                } else {
                    return false;
                }
            }
        } else {
            if (numbers.at(i) - numbers.at(i + 1) < numbers.size() && numbers.at(i) - numbers.at(i + 1) != 0) {
                if (count.find(numbers.at(i) - numbers.at(i + 1)) == count.end()) {
                    count.insert(numbers.at(i) - numbers.at(i + 1));
                } else {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    fstream file;
    file.open("Jolly.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int number;
        vector<int> numbers = vector<int>();
        while (!file.eof()) {
            int times;
            file >> times;
            for (int i = 0; i < times; i++) {
                file >> number;
                numbers.push_back(number);
            }
            if (jollyCount(numbers)) {
                cout << "Jolly" << endl;
            } else {
                cout << "Not jolly" << endl;
            }
            numbers.clear();
        }
    }
}
