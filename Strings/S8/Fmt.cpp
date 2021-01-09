//
// Created by Oğuz Kerem Yıldız on 9.01.2021.
//
#include <iostream>
#include <fstream>

using namespace std;

void print(string &added) {
    string word = "";
    string remaining = "";
    int t = 0;
    if (added.at(0) == ' ') {
        while (added.at(t) == ' ') {
            remaining += " ";
            t++;
        }
    }
    for (int i = 0; i < added.length(); i++) {
        if (added.at(i) != ' ') {
            word += added.at(i);
        } else {
            if (remaining.length() + word.length() < 72) {
                if (remaining.length() == 0){
                    remaining = word;
                } else {
                    remaining += " " + word;
                }
            } else {
                cout << remaining << endl;
                remaining = word;
            }
            word = "";
        }
    }
    if (word.length() != 0){
        remaining += " " + word;
    }
    cout << remaining << endl;
}

int main() {
    fstream file;
    file.open("Unix.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        string line;
        string added = "";
        int i = 0;
        while (!file.eof()) {
            getline(file, line);
            if (line != "") {
                if (i == 0) {
                    added += "";
                    i++;
                } else {
                    added += " ";
                }
                added += line;
            } else {
                if (added.length() > 72) {
                    print(added);
                    cout << "" << endl;
                    added = "";
                    i = 0;
                } else {
                    cout << added;
                    added = "";
                    cout << "" << endl;
                    i = 0;
                }
            }
        }
    }
}