//
// Created by Oğuz Kerem Yıldız on 8.01.2021.
//
#include <fstream>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

void graphAdd(unordered_map<string , vector<string>> &match, vector<string> numbers) {
    string combine;
    for (int j = 0; j < numbers.size(); j++) {
        for (int t = 0; t < numbers.size(); t++) {
            if (j != t) {
                combine = numbers.at(j) + numbers.at(t);
                match[numbers.at(j)].push_back(combine);
            }
        }
    }
}

void addAllElement(vector<string> &allElements, unordered_map<string, vector<string>> match, vector<string> &numbers) {
    for (const string& number : numbers) {
        allElements.insert(allElements.end(), match[number].begin(), match[number].end());
    }
}

void find(vector<string> &allElements, vector<string> numbers) {
    int times = 0;
    int count;
    int count1;
    int count2;
    int count3;
    vector<string> isHave = vector<string>();
    for (const string& allElement : allElements) {
        for (int j = 0; j < numbers.size(); j++) {
            count = 0;
            count1 = 0;
            count2 = 0;
            count3 = 0;
            for (int t = 0; t < numbers.size(); t++) {
                if (t != j) {
                    for (const string& s : isHave) {
                        if (s == numbers.at(j)) {
                            count++;
                        }
                        if (s == numbers.at(t)) {
                            count2++;
                        }
                    }
                    for (const string& number : numbers) {
                        if (number == numbers.at(j)) {
                            count1++;
                        }
                        if (number == numbers.at(t)) {
                            count3++;
                        }
                    }
                    if (count != count1 && count2 != count3) {
                        if (allElement == numbers.at(j) + numbers.at(t)) {
                            isHave.push_back(numbers.at(j));
                            isHave.push_back(numbers.at(t));
                            times += 2;
                            break;
                        }
                    }
                }
            }
        }
        if (times == numbers.size()) {
            cout << allElement << endl;
            break;
        } else {
            times = 0;
        }
        isHave.clear();
    }
}

int main() {
    fstream file;
    file.open("FileFragmentation.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        vector<string> allElements = vector<string>();
        unordered_map<string, vector<string>> match = unordered_map<string, vector<string>>();
        vector<string> numbers = vector<string>();
        string line;
        while (!file.eof()) {
            getline(file, line);
            numbers.push_back(line);
        }
        graphAdd(match, numbers);
        addAllElement(allElements, match, numbers);
        find(allElements, numbers);
    }
}