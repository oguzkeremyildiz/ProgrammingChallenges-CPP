//
// Created by Oğuz Kerem Yıldız on 7.01.2021.
//
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

bool equals(char a, char b) {
    return tolower(a) == tolower(b);
}

void findWord(string **table, string *words, int tableLength1, int tableLength2, int wordLength) {
    int wordSize = 1;
    for (int i = 0; i < wordLength; i++) {
        string word = words[i];
        for (int j = 0; j < tableLength1; j++) {
            for (int k = 0; k < tableLength2; k++) {
                if (equals(word.at(0), table[j][k].at(0))) {
                    if (j - 1 >= 0 && k - 1 >= 0) {
                        wordSize = 1;
                        if (equals(word.at(1), table[j - 1][k - 1].at(0))) {
                            for (int m = 1; m <= wordLength - 1; m++) {
                                if (j - m >= 0 && k - m >= 0) {
                                    if (equals(word.at(m), table[j - m][k - m].at(0))) {
                                        wordSize++;
                                    }
                                }
                            }
                            if (wordSize == word.length()) {
                                cout << to_string(j + 1) + " " + to_string(k + 1) << endl;
                                break;
                            }
                        }
                    }
                    if (j - 1 >= 0 && k + 1 < tableLength2) {
                        wordSize = 1;
                        if (equals(word.at(1), table[j - 1][k + 1].at(0))) {
                            for (int m = 1; m <= word.length() - 1; m++) {
                                if (j - m >= 0 && k + m < tableLength2) {
                                    if (equals(word.at(m), table[j - m][k + m].at(0))) {
                                        wordSize++;
                                    }
                                }
                            }
                            if (wordSize == word.length()) {
                                cout << to_string(j + 1) + " " + to_string(k + 1) << endl;
                                break;
                            }
                        }
                    }
                    if (j + 1 < tableLength1 && k - 1 >= 0) {
                        wordSize = 1;
                        if (equals(word.at(1), table[j + 1][k - 1].at(0))) {
                            for (int m = 1; m <= word.length() - 1; m++) {
                                if (j + m < tableLength1 && k - m >= 0) {
                                    if (equals(word.at(m), table[j + m][k - m].at(0))) {
                                        wordSize++;
                                    }
                                }
                            }
                            if (wordSize == word.length()) {
                                cout << to_string(j + 1) + " " + to_string(k + 1) << endl;
                                break;
                            }
                        }
                    }
                    if (j + 1 < tableLength1 && k + 1 < tableLength2) {
                        wordSize = 1;
                        if (equals(word.at(1), table[j + 1][k + 1].at(0))) {
                            for (int m = 1; m <= word.length() - 1; m++) {
                                if (j + m < tableLength1 && k + m < tableLength2) {
                                    if (equals(word.at(m), table[j + m][k + m].at(0))) {
                                        wordSize++;
                                    }
                                }
                            }
                            if (wordSize == word.length()) {
                                cout << to_string(j + 1) + " " + to_string(k + 1) << endl;
                                break;
                            }
                        }
                    }
                    if (j + 1 < tableLength1) {
                        wordSize = 1;
                        if (equals(word.at(1), table[j + 1][k].at(0))) {
                            for (int m = 1; m <= word.length() - 1; m++) {
                                if (j + m < tableLength1) {
                                    if (equals(word.at(m), table[j + m][k].at(0))) {
                                        wordSize++;
                                    }
                                }
                            }
                            if (wordSize == word.length()) {
                                cout << to_string(j + 1) + " " + to_string(k + 1) << endl;
                                break;
                            }
                        }
                    }
                    if (j - 1 >= 0) {
                        wordSize = 1;
                        if (equals(word.at(1), table[j - 1][k].at(0))) {
                            for (int m = 1; m <= word.length() - 1; m++) {
                                if (j - m >= 0) {
                                    if (equals(word.at(m), table[j - m][k].at(0))) {
                                        wordSize++;
                                    }
                                }
                            }
                            if (wordSize == word.length()) {
                                cout << to_string(j + 1) + " " + to_string(k + 1) << endl;
                                break;
                            }
                        }
                    }
                    if (k + 1 < tableLength2) {
                        wordSize = 1;
                        if (equals(word.at(1), table[j][k + 1].at(0))) {
                            for (int m = 1; m <= word.length() - 1; m++) {
                                if (k + m <= tableLength1) {
                                    if (equals(word.at(m), table[j][k + m].at(0))) {
                                        wordSize++;
                                    }
                                }
                            }
                            if (wordSize == word.length()) {
                                cout << to_string(j + 1) + " " + to_string(k + 1) << endl;
                                break;
                            }
                        }
                    }
                    if (k - 1 >= 0) {
                        if (equals(word.at(1), table[j][k - 1].at(0))) {
                            wordSize = 1;
                            for (int m = 1; m <= word.length() - 1; m++) {
                                if (k - m >= 0) {
                                    if (equals(word.at(m), table[j][k - m].at(0))) {
                                        wordSize++;
                                    }
                                }
                            }
                            if (wordSize == word.length()) {
                                cout << to_string(j + 1) + " " + to_string(k + 1) << endl;
                                break;
                            }
                        }
                    }
                }
            }
            if (wordSize == wordLength) {
                wordSize = 1;
                break;
            }
        }
    }
}

int main() {
    fstream file;
    file.open("Waldorf.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int tables, horizontal, vertical, wordsNumber;
        file >> tables;
        string **table;
        string *words;
        string question, currentCharacter;
        for (int i = 0; i < tables; i++) {
            file >> vertical;
            file >> horizontal;
            table = (string **)malloc(vertical * sizeof(string *));
            for (int t = 0; t < vertical; t++) {
                table[t] = (string*) malloc(horizontal * sizeof(string));
            }
            for (int j = 0; j < vertical; j++) {
                for (int k = 0; k < horizontal; k++) {
                    file >> currentCharacter;
                    table[j][k] = currentCharacter;
                }
            }
            file >> wordsNumber;
            words = new string[wordsNumber];
            for (int t = 0; t < wordsNumber; t++){
                file >> question;
                words[t] = question;
            }
            findWord(table, words, vertical, horizontal, wordsNumber);
        }
    }
}