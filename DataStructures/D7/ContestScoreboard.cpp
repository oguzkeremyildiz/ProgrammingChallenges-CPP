//
// Created by Oğuz Kerem Yıldız on 5.01.2021.
//
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;

void print(unordered_map<int, int> totalMinutes, unordered_map<int, int> questions) {
    int person;
    int minute;
    int value;
    vector<pair<int, int>> v1 = vector<pair<int, int>>();
    vector<int> v2 = vector<int>();
    for (auto &item : totalMinutes) {
        v1.emplace_back(item.first, item.second);
    }
    for (auto &question : questions) {
        v2.push_back(question.second);
    }
    for (int i = 0; i < v1.size(); i++) {
        person = v1.at(i).first;
        minute = v1.at(i).second;
        value = v2.at(i);
        cout << to_string(person) + " ";
        cout << to_string(value) + " ";
        cout << to_string(minute) + " ";
        cout << "" << endl;
    }
}

void score(int person, int minute, string type, unordered_map<int, int> &totalMinutes,  unordered_map<int, int> &questions) {
    int currentMinute, total;
    if (type == "I") {
        if (totalMinutes.find(person) == totalMinutes.end()) {
            totalMinutes[person] = 20;
        } else {
            currentMinute = totalMinutes[person] + 20;
            totalMinutes[person] = currentMinute;
        }
    } else if (type == "C"){
        if (questions.find(person) != questions.end()) {
            total = questions[person] + 1;
            questions[person] = total;
        } else {
            questions[person] = 1;
        }
        if (totalMinutes.find(person) == totalMinutes.end()) {
            totalMinutes[person] = minute;
        } else {
            currentMinute = totalMinutes[person] + minute;
            totalMinutes[person] = currentMinute;
        }
    }
}

int main() {
    fstream file;
    file.open("Scoreboard.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int times, person, question, minute;
        string type;
        file >> times;
        for (int i = 0; i < times; i++) {
            unordered_map<int, int> totalMinutes = unordered_map<int, int>();
            unordered_map<int, int> questions = unordered_map<int, int>();
            while (!file.eof()) {
                file >> person;
                file >> question;
                file >> minute;
                file >> type;
                score(person, minute, type, totalMinutes, questions);
            }
            print(totalMinutes, questions);
        }
    }
}