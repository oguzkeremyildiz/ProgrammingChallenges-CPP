//
// Created by Oğuz Kerem Yıldız on 12.01.2021.
//
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "Elephant.h"

using namespace std;

void print(vector<int> &longest) {
    cout << "[";
    bool first = true;
    for (int i : longest) {
        if (!first) {
            cout << ", " + to_string(i);
        } else {
            cout << to_string(i);
            first = false;
        }
    }
    cout << "]" << endl;
}

vector<int> setList(vector<Elephant> &elephantList) {
    vector<int> list = vector<int>();
    for (Elephant elephant : elephantList) {
        list.push_back(elephant.getIq());
    }
    return list;
}

vector<int> setLongest(int start, unordered_map<int, int> &map) {
    vector<int> list = vector<int>();
    int current = start;
    while (map.find(current) != map.end()) {
        list.push_back(current);
        current = map[current];
    }
    list.push_back(current);
    return list;
}

vector<int> longestDecreasingSequence(vector<int> &list) {
    unordered_map<int, int> map = unordered_map<int, int>();
    int *array = new int[list.size()];
    vector<int> longest;
    for (int i = 0; i < list.size(); ++i) {
        array[i] = 1;
    }
    for (int i = 1; i < list.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (list.at(j) > list.at(i) && array[i] <= array[j]) {
                map[list.at(i)] = list.at(j);
                array[i] = array[j] + 1;
            }
        }
    }
    int best = 0;
    int bestNumber = 0;
    for (int i = 0; i < list.size(); i++) {
        int value = array[i];
        if (value > best) {
            bestNumber = list.at(i);
            best = value;
        }
    }
    cout << best << endl;
    longest = setLongest(bestNumber, map);
    return longest;
}

void sort(vector<Elephant> &elephantList) {
    vector<Elephant> removeList = vector<Elephant>();
    for (int i = 0; i < elephantList.size(); i++) {
        for (int j = 0; j < elephantList.size(); j++) {
            if (i != j) {
                if (elephantList.at(i).getWeight() < elephantList.at(j).getWeight()) {
                    Elephant temporary = elephantList.at(i);
                    elephantList.at(i) = elephantList.at(j);
                    elephantList.at(j) = temporary;
                } else if (elephantList.at(i).getWeight() == elephantList.at(j).getWeight()) {
                    if (elephantList.at(i).getIq() > elephantList.at(j).getIq()) {
                        removeList.push_back(elephantList.at(j));
                        Elephant temporary = elephantList.at(i);
                        elephantList.at(i) = elephantList.at(j);
                        elephantList.at(j) = temporary;
                    }
                }
            }
        }
    }
    for (auto & i : removeList) {
        elephantList.erase(remove(elephantList.begin(), elephantList.end(), i), elephantList.end());
    }
}

int main() {
    fstream file;
    file.open("Smart.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        vector<Elephant> elephantList = vector<Elephant>();
        vector<int> list;
        int iterator = 0;
        while (!file.eof()) {
            iterator++;
            int first, second;
            file >> first;
            file >> second;
            elephantList.emplace_back(first, second, iterator);
        }
        sort(elephantList);
        list = setList(elephantList);
        vector<int> longest = longestDecreasingSequence(list);
        print(longest);
    }
}