//
// Created by Oğuz Kerem Yıldız on 19.01.2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

bool* setPrimes() {
    bool *primes = (bool *)calloc(10000000, sizeof(bool));
    primes[0] = true;
    for (int i = 0; i < 10000000; i++) {
        if (!primes[i]) {
            int times = 2;
            while ((i + 1) * times < 10000000) {
                primes[((i + 1) * times) - 1] = true;
                times++;
            }
        }
    }
    return primes;
}

unordered_map<int, pair<int, int>> addMap(const bool *primes) {
    unordered_map<int, pair<int, int>> couples = unordered_map<int, pair<int, int>>();
    vector<int> primesVec = vector<int>();
    for (int i = 0; i < 10000000; i++) {
        if (!primes[i] && i != 9999999) {
            if (find(primesVec.begin(), primesVec.end(), i + 1) == primesVec.end()) {
                primesVec.push_back(i + 1);
            }
        }
    }
    for (int i = 6; i <= 5000000; i += 2) {
        for (int prime : primesVec) {
            if (prime <= i) {
                if (find(primesVec.begin(), primesVec.end(), i - prime) != primesVec.end()) {
                    pair<int, int> element = pair<int, int>(prime, i - prime);
                    couples[i] = element;
                    break;
                }
            } else {
                break;
            }
        }
    }
    return couples;
}

void print(unordered_map<int, pair<int, int>> couples, int number) {
    for (auto &element : couples) {
        if (couples.find(number - element.first) != couples.end()) {
            cout << to_string(element.second.first) + " " + to_string(element.second.second) + " " + to_string(couples[number - element.first].first) + " " + to_string(couples[number - element.first].second) << endl;
            break;
        }
    }
}

int main() {
    fstream file;
    file.open("Primes.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        vector<int> numbers = vector<int>();
        unordered_map<int, pair<int, int>> couples;
        bool *primes;
        int number;
        while (!file.eof()) {
            file >> number;
            numbers.push_back(number);
        }
        primes = setPrimes();
        couples = addMap(primes);
        for (int num : numbers) {
            print(couples, num);
        }
    }
}