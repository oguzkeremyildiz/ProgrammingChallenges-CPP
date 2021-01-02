//
// Created by Oğuz Kerem Yıldız on 2.01.2021.
//

#include <iostream>
#include <fstream>
#include "Hand.h"
#include <vector>

using namespace std;

void whoWin(int pointBlack, int pointWhite) {
    if (pointBlack > pointWhite) {
        cout << "Black Wins." + to_string(pointBlack) << endl;
    } else if (pointWhite > pointBlack) {
        cout << "White Wins." + to_string(pointWhite) << endl;
    } else {
        cout << "Tie." << endl;
    }
}

void highCards(Hand blackHand, Hand whiteHand) {
    if (blackHand.compareTo(whiteHand) > 0) {
        cout << "Black Wins." << endl;
    } else {
        if (blackHand.compareTo(whiteHand) < 0) {
            cout << "White Wins." << endl;
        } else {
            cout << "Tie." << endl;
        }
    }
}

int main() {
    fstream file;
    file.open("Poker.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int pointBlack = 0, pointWhite = 0, size;
        file >> size;
        string line;
        for (int i = 0; i < size; i++) {
            Hand blackHand = Hand();
            Hand whiteHand = Hand();
            for (int j = 0; j < 10; j++) {
                file >> line;
                if (j < 5) {
                    blackHand.addCard(Card(line));
                } else {
                    whiteHand.addCard(Card(line));
                }
                if (j == 9) {
                    blackHand.quickSort(0, blackHand.size() - 1);
                    whiteHand.quickSort(0, whiteHand.size() - 1);
                    if (blackHand.straightFlush()) {
                        pointBlack = 9;
                    } else if (blackHand.fourOfAKind()) {
                        pointBlack = 8;
                    } else if (blackHand.fullHouse()) {
                        pointBlack = 7;
                    }  else if (blackHand.flush()) {
                        pointBlack = 6;
                    } else if (blackHand.straight()) {
                        pointBlack = 5;
                    } else if (blackHand.threeOfAKind() == 1) {
                        pointBlack = 4;
                    } else if (blackHand.twoPairs() == 1) {
                        pointBlack = 3;
                    } else if (blackHand.pair() != 0) {
                        pointBlack = 2;
                    }
                    if (whiteHand.straightFlush()) {
                        pointWhite = 9;
                    } else if (whiteHand.fourOfAKind()) {
                        pointWhite = 8;
                    } else if (whiteHand.fullHouse()) {
                        pointWhite = 7;
                    } else if (whiteHand.flush()) {
                        pointWhite = 6;
                    } else if (whiteHand.straight()) {
                        pointWhite = 5;
                    } else if (whiteHand.threeOfAKind() == 1) {
                        pointWhite = 4;
                    } else if (whiteHand.twoPairs() == 1) {
                        pointWhite = 3;
                    } else if (whiteHand.pair() != 0) {
                        pointWhite = 2;
                    }
                    if (pointBlack == 5 && pointWhite == 5) {
                        highCards(blackHand, whiteHand);
                    } else if (pointBlack == 6 && pointWhite == 6) {
                        highCards(blackHand, whiteHand);
                    } else if (pointBlack == 0 && pointWhite == 0) {
                        highCards(blackHand, whiteHand);
                    } else if (pointBlack == 3 && pointWhite == 3) {
                        if (blackHand.twoPairs() != whiteHand.twoPairs()) {
                            whoWin(blackHand.twoPairs(), whiteHand.twoPairs());
                        } else {
                            highCards(blackHand, whiteHand);
                        }
                    } else if (pointBlack == 4 && pointWhite == 4) {
                        if (blackHand.threeOfAKind() != whiteHand.threeOfAKind()){
                            whoWin(blackHand.threeOfAKind(), blackHand.threeOfAKind());
                        } else {
                            highCards(blackHand, whiteHand);
                        }
                    } else if (pointBlack == 2 && pointWhite == 2) {
                        if (blackHand.pair() != whiteHand.pair()){
                            whoWin(blackHand.pair(), whiteHand.pair());
                        } else {
                            highCards(blackHand, whiteHand);
                        }
                    } else {
                        whoWin(pointBlack, pointWhite);
                    }
                    pointBlack = 0;
                    pointWhite = 0;
                }
            }
        }
    }
}