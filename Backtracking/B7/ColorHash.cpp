//
// Created by Oğuz Kerem Yıldız on 29.01.2021.
//
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

static vector<int> found;
static vector<int> solution = vector<int>();

void addSolution() {
    solution.push_back(0);
    solution.push_back(3);
    solution.push_back(4);
    solution.push_back(3);
    solution.push_back(0);
    solution.push_back(5);
    solution.push_back(6);
    solution.push_back(5);
    solution.push_back(0);
    solution.push_back(1);
    solution.push_back(2);
    solution.push_back(1);
    solution.push_back(0);
    solution.push_back(7);
    solution.push_back(8);
    solution.push_back(7);
    solution.push_back(0);
    solution.push_back(9);
    solution.push_back(10);
    solution.push_back(9);
    solution.push_back(0);
    solution.push_back(1);
    solution.push_back(2);
    solution.push_back(1);
}

int remaining(vector<int> sequence) {
    int returning = -1;
    int remaining = 1;
    for (int i = 0; i < sequence.size(); i++) {
        if (i + 1 < sequence.size()) {
            if (sequence.at(i) == sequence.at(i + 1)) {
                remaining++;
            } else {
                remaining = 1;
            }
            if (remaining == 5 && i + 1 == sequence.size() - 1) {
                returning = sequence.at(i);
                break;
            }
        }
    }
    return returning;
}

bool isASolution(const vector<int>& table) {
    return table == solution;
}

void constructCandidates(vector<int> &subsets, vector<int> sequence) {
    if (!sequence.empty()) {
        switch (sequence.at(sequence.size() - 1)) {
            case 1:
                if (remaining(sequence) != 1) {
                    subsets.push_back(1);
                }
                subsets.push_back(2);
                subsets.push_back(4);
                break;
            case 2:
                if (remaining(sequence) != 2) {
                    subsets.push_back(2);
                }
                subsets.push_back(1);
                subsets.push_back(3);
                break;
            case 3:
                if (remaining(sequence) != 3) {
                    subsets.push_back(3);
                }
                subsets.push_back(2);
                subsets.push_back(4);
                break;
            default:
                if (remaining(sequence) != 4) {
                    subsets.push_back(4);
                }
                subsets.push_back(1);
                subsets.push_back(3);
                break;
        }
    } else {
        subsets.push_back(1);
        subsets.push_back(2);
        subsets.push_back(3);
        subsets.push_back(4);
    }
}

void rotate(vector<int> &table, int subset) {
    vector<int> clone = vector<int>(table);
    switch (subset) {
        case 1:
            for (int i = 0; i < 12; i++) {
                if (i > 1) {
                    table.at(i) = clone.at(i - 2);
                } else if (i == 0) {
                    table.at(0) = clone.at(10);
                } else {
                    table.at(1) = clone.at(11);
                }
            }
            table.at(21) = table.at(9);
            table.at(22) = table.at(10);
            table.at(23) = table.at(11);
            break;
        case 2:
            for (int i = 12; i < table.size(); i++) {
                if (i < 22) {
                    table.at(i) = clone.at(i + 2);
                } else if (i == 22) {
                    table.at(22) = clone.at(12);
                } else {
                    table.at(23) = clone.at(13);
                }
            }
            table.at(9) = table.at(21);
            table.at(10) = table.at(22);
            table.at(11) = table.at(23);
            break;
        case 3:
            for (int i = 0; i < 12; i++) {
                if (i < 10) {
                    table.at(i) = clone.at(i + 2);
                } else if (i == 10) {
                    table.at(10) = clone.at(0);
                } else {
                    table.at(11) = clone.at(1);
                }
            }
            table.at(21) = table.at(9);
            table.at(22) = table.at(10);
            table.at(23) = table.at(11);
            break;
        default:
            for (int i = 12; i < table.size(); i++) {
                if (i > 13) {
                    table.at(i) = clone.at(i - 2);
                } else if (i == 12) {
                    table.at(12) = clone.at(22);
                } else {
                    table.at(13) = clone.at(23);
                }
            }
            table.at(9) = table.at(21);
            table.at(10) = table.at(22);
            table.at(11) = table.at(23);
            break;
    }
}

void backtrack(vector<int> &table, vector<int> &sequence) {
    if (found.size() == 16) {
        return;
    }
    if (!found.empty()) {
        if (sequence.size() >= found.size()) {
            return;
        }
    }
    vector<int> subsets = vector<int>();
    vector<int> tableClone;
    if (isASolution(table)) {
        if (!sequence.empty()) {
            found.clear();
            found.insert(found.end(), sequence.begin(), sequence.end());
        } else {
            cout << "PUZZLE ALREADY SOLVED" << endl;
        }
    } else {
        constructCandidates(subsets, sequence);
        for (int subset : subsets) {
            sequence.push_back(subset);
            tableClone = vector<int>(table);
            rotate(table, subset);
            if (sequence.size() != 16) {
                backtrack(table, sequence);
            } else {
                if (isASolution(table)) {
                    found.clear();
                    found.insert(found.end(), sequence.begin(), sequence.end());
                }
            }
            sequence.pop_back();
            table.clear();
            table.insert(table.end(), tableClone.begin(), tableClone.end());
        }
    }
}

string toStringFound() {
    string str = "[";
    for (int i = 0; i < found.size(); ++i) {
        if (i + 1 == found.size()) {
            str += to_string(found.at(i));
        } else {
            str += to_string(found.at(i)) + ", ";
        }
    }
    str += "]";
    return str;
}

int main() {
    fstream file;
    file.open("ColorHash.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        found = vector<int>();
        addSolution();
        vector<int> table = vector<int>();
        int times, hash;
        file >> times;
        for (int i = 0; i < times; i++) {
            for (int j = 0; j < 24; j++) {
                file >> hash;
                table.push_back(hash);
            }
            vector<int> v = vector<int>();
            backtrack(table, v);
            if (!found.empty() || isASolution(table)) {
                if (!found.empty()) {
                    cout << toStringFound() << endl;
                }
            } else {
                cout << "NO SOLUTION WAS FOUND IN 16 STEPS" << endl;
            }
            found.clear();
            table.clear();
        }
    }
}