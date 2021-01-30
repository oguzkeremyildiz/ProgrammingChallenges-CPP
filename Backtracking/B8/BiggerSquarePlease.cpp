//
// Created by Oğuz Kerem Yıldız on 30.01.2021.
//
#include <vector>
#include <iostream>
#include <fstream>
#include "Tuple/Quartet.h"
#include <unordered_set>
#include <cmath>

using namespace std;

static int totalSquare;
static int **bestBoard;
static int *minimumSquares;
static int numberOfPossibilities;

struct quartet_hash
{
    template <class T1, class T2, class T3, class T4>
    std::size_t operator() (const Quartet<T1, T2, T3, T4> &quartet) const
    {
        return std::hash<T1>()(quartet.getA()) ^ std::hash<T2>()(quartet.getB()) ^ std::hash<T3>()(quartet.getC()) ^ std::hash<T4>()(quartet.getD());
    }
};

int lengthBoard(int **board, int t, int j, int size) {
    int length = 0;
    for (int i = 0; i < size - j; i++) {
        if (board[t][j + i] == 0) {
            length++;
        } else {
            break;
        }
    }
    return length;
}

bool checkBoard(int **board, int i, int j, int length, int size) {
    bool boolean = true;
    for (int k = 0; k < length; k++) {
        for (int l = 0; l < length; l++) {
            if (i + k < size) {
                if (board[i + k][j + l] > 0) {
                    boolean = false;
                    break;
                }
            } else {
                boolean = false;
                break;
            }
        }
    }
    return boolean;
}

int allSquareOfTheNumber(const vector<int>& sequence) {
    int sum = 0;
    for (int element : sequence) {
        sum += element * element;
    }
    return sum;
}

static vector<Quartet<int, int, int, int>> lengthForPossibilities(int **board, int i, int size) {
    vector<Quartet<int, int, int, int>> list = vector<Quartet<int, int, int, int>>();
    int length = 0;
    int start = 0;
    int finish;
    for (int k = 0; k < size; k++) {
        if (board[i][k] == 0) {
            length++;
            if (k + 1 >= size) {
                finish = size - 1;
                list.emplace_back(i, length, start, finish);
            }
        } else {
            if (length > 0) {
                finish = k - 1;
                list.emplace_back(i, length, start, finish);
            }
            length = 0;
            start = k + 1;
        }
    }
    return list;
}

bool equals(Quartet<int, int, int, int> q1, Quartet<int, int, int, int> q2) {
    return q1.getB() == q2.getB() && q1.getC() == q2.getC() && q1.getD() == q2.getD();
}

int possibleSquareSize(int **board, int length) {
    vector<Quartet<int, int, int, int>> lengthList = vector<Quartet<int, int, int, int>>();
    unordered_set<Quartet<int, int, int, int>, quartet_hash> lengthSet = unordered_set<Quartet<int, int, int, int>, quartet_hash>();
    bool check;
    int currentLine;
    int times;
    int square = 0;
    for (int i = 0; i < length; i++) {
        vector<Quartet<int, int, int, int>> list = lengthForPossibilities(board, i, length);
        lengthList.insert(lengthList.end(), list.begin(), list.end());
    }
    for (int j = 0; j < lengthList.size(); j++) {
        if (lengthSet.find(lengthList.at(j)) == lengthSet.end()) {
            check = false;
            times = 1;
            currentLine = lengthList.at(j).getA();
            for (int i = 0; i < lengthList.size(); i++) {
                if (lengthSet.find(lengthList.at(i)) == lengthSet.end()) {
                    if (i != j && times != lengthList.at(j).getB()) {
                        if (equals(lengthList.at(i), lengthList.at(j))) {
                            if (currentLine + 1 == lengthList.at(i).getA()) {
                                times++;
                                if (!check) {
                                    square++;
                                }
                                check = true;
                                lengthSet.insert(lengthList.at(i));
                                currentLine = lengthList.at(i).getA();
                            }
                        }
                    }
                }
            }
            lengthSet.insert(lengthList.at(j));
            if (!check) {
                square++;
            }
        }
    }
    return square;
}

void constructCandidates(int **board, vector<int> &subsets, const vector<int>& sequence, int size) {
    numberOfPossibilities++;
    int sum = 0;
    for (int integer : sequence) {
        sum += integer * integer;
    }
    int difference = size * size - sum;
    if (sequence.size() + minimumSquares[difference] >= totalSquare){
        return;
    }
    if (sequence.size() + possibleSquareSize(board, size) >= totalSquare) {
        if (totalSquare > 0) {
            return;
        }
    }
    bool check = false;
    int length;
    if (!sequence.empty()) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == 0) {
                    length = lengthBoard(board, i , j, size);
                    for (int k = 0; k < length; k++) {
                        if (checkBoard(board, i , j, k + 1, size)) {
                            if (allSquareOfTheNumber(sequence) + ((k + 1) * (k + 1)) <= size * size) {
                                subsets.push_back(k + 1);
                            }
                        }
                    }
                    check = true;
                    break;
                }
            }
            if (check) {
                break;
            }
        }
    } else {
        for (int i = 1; i < size; i++) {
            subsets.push_back(i);
        }
        if (subsets.size() > 2) {
            if (size % 3 == 0) {
                iter_swap(subsets.begin() + (size / 3) * 2 - 1, subsets.begin() + subsets.size() - 1);
            } else {
                iter_swap(subsets.begin() + subsets.size() / 2, subsets.begin() + subsets.size() - 1);
            }
        }
    }
    reverse(subsets.begin(), subsets.end());
}

void fill(int **board, int subset, int length) {
    bool check = false;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (board[i][j] == 0) {
                for (int k = 0; k < subset; k++) {
                    for (int l = 0; l < subset; l++) {
                        if (i + k < length && j + l < length) {
                            board[i + k][j + l] = subset;
                        }
                    }
                }
                check = true;
                break;
            }
        }
        if (check) {
            break;
        }
    }
}

bool isASolution(int **board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

void clone(int **board, int **boardClone, int length) {
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            boardClone[i][j] = board[i][j];
        }
    }
}

void backtrack(int **board, vector<int> &sequence, int length) {
    if (length % 3 == 0) {
        if (totalSquare == 6) {
            return;
        }
    } else {
        if (totalSquare == 8) {
            return;
        }
    }
    if (totalSquare < sequence.size()) {
        return;
    }
    int **boardClone;
    boardClone = (int **)calloc(length, sizeof(int *));
    for (int j = 0; j < length; ++j) {
        boardClone[j] = (int*) calloc(length, sizeof(int));
    }
    vector<int> subsets = vector<int>();
    if (sequence.size() > 5 && allSquareOfTheNumber(sequence) == (length * length) && isASolution(board, length)) {
        if (sequence.size() < totalSquare) {
            totalSquare = sequence.size();
            bestBoard = board;
        }
    } else {
        constructCandidates(board, subsets, sequence, length);
        for (int subset : subsets) {
            sequence.push_back(subset);
            clone(board, boardClone, length);
            fill(board, subset, length);
            backtrack(board, sequence, length);
            sequence.pop_back();
            board = boardClone;
        }
    }
}

void fillForTwo(int size) {
    int element = size / 2;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            bestBoard[i][j] = element;
        }
    }
}

void findMinimumSquares() {
    minimumSquares = (int*) calloc(2500, sizeof(int));
    minimumSquares[0] = 0;
    minimumSquares[1] = 1;
    minimumSquares[2] = 2;
    minimumSquares[3] = 3;
    minimumSquares[4] = 1;
    int min;
    for (int i = 5; i < 2500; i++) {
        if (i == ((int) sqrt(i)) * ((int) sqrt(i))) {
            min = 1;
        } else {
            min = minimumSquares[i - 1] + 1;
        }
        int j = 2;
        while (i - j * j > 1){
            if (minimumSquares[i - j * j] + 1 < min){
                min = minimumSquares[i - j * j] + 1;
            }
            j++;
        }
        minimumSquares[i] = min;
    }
}

void print(int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            cout << bestBoard[i][j];
        }
        cout << "" << endl;
    }
}

int main() {
    fstream file;
    file.open("Square.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        findMinimumSquares();
        int times, size;
        file >> times;
        for (int i = 0; i < times; i++) {
            totalSquare = 10000;
            numberOfPossibilities = 0;
            file >> size;
            int **board;
            board = (int **)calloc(size, sizeof(int *));
            for (int j = 0; j < size; ++j) {
                board[j] = (int*) calloc(size, sizeof(int));
            }
            bestBoard = (int **)calloc(size, sizeof(int *));
            for (int j = 0; j < size; ++j) {
                bestBoard[j] = (int*) calloc(size, sizeof(int));
            }
            if (size % 2 == 1) {
                vector<int> v = vector<int>();
                backtrack(board, v, size);
            } else {
                totalSquare = 4;
                fillForTwo(size);
            }
            cout << numberOfPossibilities << endl;
            cout << totalSquare << endl;
            print(size);
        }
    }
}