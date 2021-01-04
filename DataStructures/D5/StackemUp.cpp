//
// Created by Oğuz Kerem Yıldız on 4.01.2021.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

void print(vector<string> value, vector<string> suit) {
    for (int i = 0; i < value.size(); i++) {
        cout << value.at(i) + " of " + suit.at(i) << endl;
    }
}

void normalDeck(vector<string> &value, vector<string> &suit) {
    value.emplace_back("2");
    suit.emplace_back("Clubs");
    value.emplace_back("3");
    suit.emplace_back("Clubs");
    value.emplace_back("4");
    suit.emplace_back("Clubs");
    value.emplace_back("5");
    suit.emplace_back("Clubs");
    value.emplace_back("6");
    suit.emplace_back("Clubs");
    value.emplace_back("7");
    suit.emplace_back("Clubs");
    value.emplace_back("8");
    suit.emplace_back("Clubs");
    value.emplace_back("9");
    suit.emplace_back("Clubs");
    value.emplace_back("10");
    suit.emplace_back("Clubs");
    value.emplace_back("Jack");
    suit.emplace_back("Clubs");
    value.emplace_back("Queen");
    suit.emplace_back("Clubs");
    value.emplace_back("King");
    suit.emplace_back("Clubs");
    value.emplace_back("Ace");
    suit.emplace_back("Clubs");
    value.emplace_back("2");
    suit.emplace_back("Diamonds");
    value.emplace_back("3");
    suit.emplace_back("Diamonds");
    value.emplace_back("4");
    suit.emplace_back("Diamonds");
    value.emplace_back("5");
    suit.emplace_back("Diamonds");
    value.emplace_back("6");
    suit.emplace_back("Diamonds");
    value.emplace_back("7");
    suit.emplace_back("Diamonds");
    value.emplace_back("8");
    suit.emplace_back("Diamonds");
    value.emplace_back("9");
    suit.emplace_back("Diamonds");
    value.emplace_back("10");
    suit.emplace_back("Diamonds");
    value.emplace_back("Jack");
    suit.emplace_back("Diamonds");
    value.emplace_back("Queen");
    suit.emplace_back("Diamonds");
    value.emplace_back("King");
    suit.emplace_back("Diamonds");
    value.emplace_back("Ace");
    suit.emplace_back("Diamonds");
    value.emplace_back("2");
    suit.emplace_back("Hearts");
    value.emplace_back("3");
    suit.emplace_back("Hearts");
    value.emplace_back("4");
    suit.emplace_back("Hearts");
    value.emplace_back("5");
    suit.emplace_back("Hearts");
    value.emplace_back("6");
    suit.emplace_back("Hearts");
    value.emplace_back("7");
    suit.emplace_back("Hearts");
    value.emplace_back("8");
    suit.emplace_back("Hearts");
    value.emplace_back("9");
    suit.emplace_back("Hearts");
    value.emplace_back("10");
    suit.emplace_back("Hearts");
    value.emplace_back("Jack");
    suit.emplace_back("Hearts");
    value.emplace_back("Queen");
    suit.emplace_back("Hearts");
    value.emplace_back("King");
    suit.emplace_back("Hearts");
    value.emplace_back("Ace");
    suit.emplace_back("Hearts");
    value.emplace_back("2");
    suit.emplace_back("Spades");
    value.emplace_back("3");
    suit.emplace_back("Spades");
    value.emplace_back("4");
    suit.emplace_back("Spades");
    value.emplace_back("5");
    suit.emplace_back("Spades");
    value.emplace_back("6");
    suit.emplace_back("Spades");
    value.emplace_back("7");
    suit.emplace_back("Spades");
    value.emplace_back("8");
    suit.emplace_back("Spades");
    value.emplace_back("9");
    suit.emplace_back("Spades");
    value.emplace_back("10");
    suit.emplace_back("Spades");
    value.emplace_back("Jack");
    suit.emplace_back("Spades");
    value.emplace_back("Queen");
    suit.emplace_back("Spades");
    value.emplace_back("King");
    suit.emplace_back("Spades");
    value.emplace_back("Ace");
    suit.emplace_back("Spades");
}

void shuffle(vector<int> current, vector<string> &value, vector<string> &suit) {
    int currentNumber;
    string temporaryValue, temporarySuit;
    unordered_set<int> isNum = unordered_set<int>();
    for (int i = 0; i < current.size(); i++){
        if (isNum.find(i) == isNum.end() && i > 0) {
            currentNumber = current.at(i);
            isNum.insert(currentNumber - 1);
            temporaryValue = value.at(i);
            temporarySuit = suit.at(i);
            value.at(i) = value.at(currentNumber - 1);
            value.at(currentNumber - 1) = temporaryValue;
            suit.at(i) = suit.at(currentNumber - 1);
            suit.at(currentNumber - 1) = temporarySuit;
        }
    }
}

int main() {
    fstream file;
    file.open("Deck.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int numberOfDeck, cards, cardNumber, deckNumber;
        int *values = new int[2];
        vector<string> value = vector<string>();
        vector<string> suit = vector<string>();
        normalDeck(value, suit);
        unordered_map<int, vector<int>> deckList = unordered_map<int, vector<int>>();
        vector<int> decks = vector<int>();
        vector<int> current = vector<int>();
        file >> numberOfDeck;
        file >> cards;
        deckNumber = 0;
        for (int i = 0; i < numberOfDeck; i++) {
            for (int t = 0; t < cards; t++) {
                for (int j = 1; j <= 52; j++) {
                    file >> cardNumber;
                    decks.push_back(cardNumber);
                    if (j == 52) {
                        deckNumber++;
                        deckList[deckNumber] = decks;
                        decks = vector<int>();
                    }
                }
            }
            for (int k = 0; k < cards; k++) {
                file >> values[k];
                for (int j = 0; j < deckList[values[k]].size(); j++) {
                    current.push_back(deckList[values[k]].at(j));
                }
                shuffle(current, value, suit);
                current.clear();
            }
            print(value, suit);
        }
    }
}