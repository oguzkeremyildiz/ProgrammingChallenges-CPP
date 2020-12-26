//
// Created by Oğuz Kerem Yıldız on 26.12.2020.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void choose(vector<int> streets) {
    int best = INT_MAX;
    for (int i = 0; i < streets.size(); i++) {
        int total = 0;
        for (int j = 0; j < streets.size(); j++) {
            if (i != j) {
                total += abs(streets.at(i) - streets.at(j));
            }
        }
        if (total < best) {
            best = total;
        }
    }
    cout << best << endl;
}

int main() {
    fstream file;
    file.open("Vito.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int testCase, number, street;
        vector<int> streets = vector<int>();
        file >> testCase;
        for (int i = 0; i < testCase; i++) {
            file >> number;
            for (int j = 0; j < number; j++) {
                file >> street;
                streets.push_back(street);
            }
            choose(streets);
            streets.clear();
        }
    }
}