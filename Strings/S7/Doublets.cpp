//
// Created by Oğuz Kerem Yıldız on 9.01.2021.
//
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int difference(string word, string current) {
    int difference = 0;
    if (word.length() == current.length()){
        for (int i = 0; i < current.length(); i++) {
            if (word.at(i) != current.at(i)) {
                difference++;
            }
        }
    }
    return difference;
}

void setListForOnes(unordered_map<int, vector<string>> &matches, vector<string> &dictionary, vector<string> words) {
    for (const string& s : dictionary) {
        if (difference(words.at(0), s) == 1) {
            matches[0].push_back(s);
        }
    }
}

void setListForInfinities(unordered_map<int, vector<string>> &matches, vector<string> &dictionary, vector<string> words) {
    for (const string& s : dictionary) {
        if (find(matches[0].begin(), matches[0].end(), s) == matches[0].end()) {
            if (s != words.at(0)) {
                matches[10000].push_back(s);
            }
        }
    }
}

void setList(unordered_map<int, vector<string>> &matches, int index, vector<string> &listInfinities, const string& word, vector<string> words, vector<string> &dictionary) {
    int current;
    matches[index];
    vector<string> listOnes = vector<string>(matches[index - 1]);
    for (const string& listOne : listOnes) {
        for (int j = 0; j < listInfinities.size(); j++) {
            if (difference(listOne, listInfinities.at(j)) == 1) {
                matches[index].push_back(listInfinities.at(j));
                listInfinities.erase(remove(listInfinities.begin(), listInfinities.end(), listInfinities.at(j)), listInfinities.end());
            }
        }
    }
    if (find(matches.at(index).begin(), matches.at(index).end(), words.at(1)) != matches.at(index).end()) {
        listInfinities.clear();
    }
    if (matches.find(dictionary.size() + 2) != matches.end()) {
        cout << "No solution." << endl;
        listInfinities.clear();
    }
    for (int t = 0; t < listInfinities.size(); t++){
        current = difference(word, listInfinities.at(t));
        if (matches.find(current) != matches.end()) {
            if (!matches[current].empty()) {
                listInfinities.erase(remove(listInfinities.begin(), listInfinities.end(), listInfinities.at(t)), listInfinities.end());
            }
        }
    }
}

void addList(unordered_map<int, vector<string>> &matches, vector<string> &words, int check, vector<string> &outputs) {
    string current = "";
    vector<string> removed = vector<string>();
    if (check == 0) {
        for (int t = 0; t < matches[matches.size() - 2].size(); t++) {
            if (matches[matches.size() - 2].at(t) == words.at(1)) {
                current  = matches[matches.size() - 2].at(t);
            } else {
                removed.push_back(matches[matches.size() - 2].at(t));
            }
        }
        for (const string& s : removed) {
            matches[matches.size() - 2].erase(remove(matches[matches.size() - 2].begin(), matches[matches.size() - 2].end(), s), matches[matches.size() - 2].end());
        }
        outputs.push_back(current);
        for (int i = 0; i < matches.size() - 1; i++) {
            for (int j = 0; j < matches[matches.size() - 2 - i].size(); j++) {
                if (difference(matches[matches.size() - 2 - i].at(j), current) == 1) {
                    outputs.push_back(matches[matches.size() - 2 - i].at(j));
                    current = matches[matches.size() - 2 - i].at(j);
                }
            }
        }
        outputs.push_back(words.at(0));
    }
}

void print(vector<string> outputs) {
    for (int i = 0; i < outputs.size(); i++) {
        cout << outputs.at(outputs.size() - 1 - i) << endl;
    }
}

int main() {
    fstream file;
    file.open("Doublets.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int index, check, i = 0;
        string current;
        unordered_map<int, vector<string>> matches = unordered_map<int, vector<string>>();
        vector<string> outputs = vector<string>();
        vector<string> dictionary = vector<string>();
        vector<string> listInfinities;
        vector<string> words = vector<string>();
        vector<string> split = vector<string>();
        while (!file.eof()) {
            if (i == 0) {
                getline(file, current);
                if (current != "-") {
                    dictionary.push_back(current);
                } else {
                    i++;
                }
            }
            if (i > 0) {
                words.clear();
                outputs.clear();
                index = 0;
                check = 0;
                getline(file, current);
                stringstream c(current);
                string intermediate;
                while (getline(c, intermediate, ' ')) {
                    split.push_back(intermediate);
                }
                words = vector<string>(split.begin(), split.end());
                matches.clear();
                setListForOnes(matches, dictionary, words);
                setListForInfinities(matches, dictionary, words);
                listInfinities = vector<string>(matches[10000]);
                while (!listInfinities.empty()) {
                    if (matches.find(dictionary.size() + 1) != matches.end()) {
                        check = 1;
                    }
                    index++;
                    setList(matches, index, listInfinities, words.at(0), words, dictionary);
                }
                matches[10000].erase(matches[10000].begin(), matches[10000].end());
                addList(matches, words, check, outputs);
                print(outputs);
                split.clear();
            }
        }
    }
}