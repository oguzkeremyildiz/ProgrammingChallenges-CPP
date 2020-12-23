//
// Created by Oğuz Kerem Yıldız on 23.12.2020.
//

#include <iostream>

using namespace std;

void print(string **region, int length1, int length2) {
    for (int i = 0; i < length1; i++) {
        for (int j = 0; j < length2; j++) {
            cout << region[i][j];
        }
        cout << "" << endl;
    }
}

void charL(string **region) {
    int number1, number2;
    cin >> number1;
    cin >> number2;
    string character;
    cin >> character;
    region[number2 - 1][number1 - 1] = character;
}

void charS(string **region, int length1, int length2) {
    string sentence;
    cin >> sentence;
    cout << sentence << endl;
    print(region, length1, length2);
    for (int i = 0; i < length1; i++) {
        for (int j = 0; j < length2; j++) {
            region[i][j] = "O";
        }
    }
}

void charFRecursive(string **region, int number1, int number2, string character1, string character2, int length1, int length2) {
    if (region[number1][number2] == character1) {
        region[number1][number2] = character2;
        if (number1 > 0) {
            charFRecursive(region, number1 - 1, number2, character1, character2, length1, length2);
        }
        if (number1 < length1 - 1) {
            charFRecursive(region, number1 + 1, number2, character1, character2, length1, length2);
        }
        if (number2 > 0) {
            charFRecursive(region, number1, number2 - 1, character1, character2, length1, length2);
        }
        if (number2 < length2 - 1) {
            charFRecursive(region, number1, number2 + 1, character1, character2, length1, length2);
        }
    }
}

void charF(string **region, int length1, int length2) {
    int number1, number2;
    cin >> number1;
    cin >> number2;
    string character;
    cin >> character;
    charFRecursive(region, number2 - 1, number1 - 1, region[number2 - 1][number1 - 1], character, length1, length2);
}

void charV(string **region) {
    int number1, number2, number3;
    cin >> number1;
    cin >> number2;
    cin >> number3;
    string character;
    cin >> character;
    for (int i = number2; i <= number3; i++) {
        region[i - 1][number1 - 1] = character;
    }
}

void charC(string **region, int length1, int length2) {
    for (int i = 0; i < length1; i++) {
        for (int j = 0; j < length2; j++) {
            region[i][j] = "O";
        }
    }
}

void charH(string **region) {
    int number1, number2, number3;
    cin >> number1;
    cin >> number2;
    cin >> number3;
    string character;
    cin >> character;
    for (int i = number1; i <= number2; i++) {
        region[number3 - 1][i - 1] = character;
    }
}

void charK(string **region) {
    int X1, Y1, X2, Y2;
    cin >> X1;
    cin >> Y1;
    cin >> X2;
    cin >> Y2;
    string character;
    cin >> character;
    for (int i = X1; i <= X2; i++) {
        for (int j = Y1; j <= Y2; j++) {
            region[j - 1][i - 1] = character;
        }
    }
}

int main() {
    int region1 = 0, region2 = 0;
    string character;
    string **region;
    cin >> character;
    while (character != "X") {
        if (character == "I") {
            cin >> region1;
            cin >> region2;
            region = (string **)malloc(region2 * sizeof(string *));
            for (int i = 0; i < region2; i++) {
                region[i] = (string *) malloc(region1 * sizeof(string));
            }
            for (int i = 0; i < region2; i++) {
                for (int j = 0; j < region1; j++) {
                    region[i][j] = "O";
                }
            }
        } else if (character == "L") {
            charL(region);
        } else if (character == "S") {
            charS(region, region2, region1);
        } else if (character == "F") {
            charF(region, region2, region1);
        } else if (character == "V") {
            charV(region);
        } else if (character == "C") {
            charC(region, region2, region1);
        } else if (character == "H") {
            charH(region);
        } else if (character == "K") {
            charK(region);
        }
        cin >> character;
    }
}