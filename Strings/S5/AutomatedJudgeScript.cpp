//
// Created by Oğuz Kerem Yıldız on 8.01.2021.
//
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>

using namespace std;

void print(unordered_set<int> outputs, int current) {
    if (outputs.find(3) != outputs.end()) {
        cout << "Run #" + to_string(current) + ": Wrong Answer" << endl;
    } else if (outputs.find(2) != outputs.end()) {
        cout << "Run #" + to_string(current) + ": Presentation Error" << endl;
    } else if (outputs.find(1) != outputs.end()) {
        cout << "Run #" + to_string(current) + ": Accepted" << endl;
    }
}

bool controlIntegers(vector<int> integersCorrect, vector<int> integersAnswers) {
    bool boolean = true;
    if (integersAnswers.size() == integersCorrect.size()) {
        for (int i = 0; i < integersAnswers.size(); i++) {
            if (integersAnswers.at(i) != integersCorrect.at(i)) {
                boolean = false;
                break;
            }
        }
    } else {
        boolean = false;
    }
    return boolean;
}

bool controlString(const string& correct, const string& answer) {
    bool boolean = true;
    if (correct.length() != answer.length()) {
        boolean = false;
    } else {
        for (int i = 0; i < answer.length(); i++) {
            if (answer.at(i) != correct.at(i)) {
                boolean = false;
                break;
            }
        }
    }
    return boolean;
}

void control(vector<int> &integersCorrect, vector<int> &integersAnswers, const string& correct, const string& answer, unordered_set<int> &outputs) {
    if (!integersAnswers.empty() && !integersCorrect.empty()) {
        if (controlIntegers(integersCorrect, integersAnswers)) {
            if (controlString(correct, answer)) {
                outputs.insert(1);
            }
        }
    }
    if (controlIntegers(integersCorrect, integersAnswers)) {
        if (!controlString(correct, answer)) {
            outputs.insert(2);
        }
    }
    if (!controlIntegers(integersCorrect, integersAnswers)) {
        outputs.insert(3);
    }
}

void convert(const string& inputs, vector<int> &integer) {
    for (int i = 0; i < inputs.length(); i++) {
        switch (inputs.at(i)) {
            case '0':
                integer.push_back(0);
                break;
            case '1':
                integer.push_back(1);
                break;
            case '2':
                integer.push_back(2);
                break;
            case '3':
                integer.push_back(3);
                break;
            case '4':
                integer.push_back(4);
                break;
            case '5':
                integer.push_back(5);
                break;
            case '6':
                integer.push_back(6);
                break;
            case '7':
                integer.push_back(7);
                break;
            case '8':
                integer.push_back(8);
                break;
            case '9':
                integer.push_back(9);
                break;
        }
    }
}

int main() {
    fstream file;
    file.open("Script.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int current = 0;
        int times = 1;
        string timesString, inputs;
        unordered_set<int> outputs = unordered_set<int>();
        vector<int> integersCorrect = vector<int>();
        vector<int> integersAnswers = vector<int>();
        vector<string> correct = vector<string>();
        vector<string> answer = vector<string>();
        while (times != 0) {
            current++;
            getline(file, timesString);
            times = stoi(timesString);
            for (int i = 0; i < times; i++) {
                getline(file, inputs);
                correct.push_back(inputs);
            }
            getline(file, timesString);
            times = stoi(timesString);
            for (int j = 0; j < times; j++) {
                getline(file, inputs);
                answer.push_back(inputs);
            }
            for (int i = 0; i < correct.size(); i++) {
                convert(correct.at(i), integersCorrect);
                convert(answer.at(i), integersAnswers);
                control(integersCorrect, integersAnswers, correct.at(i), answer.at(i), outputs);
                integersCorrect.clear();
                integersAnswers.clear();
            }
            print(outputs, current);
            correct.clear();
            answer.clear();
            outputs.clear();
        }
    }
}