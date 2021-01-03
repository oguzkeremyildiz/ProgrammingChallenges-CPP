//
// Created by Oğuz Kerem Yıldız on 3.01.2021.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <unordered_set>
#include <utility>

using namespace std;

unordered_map<int, vector<string>> createWordLists(vector<string> words) {
    unordered_map<int, vector<string>> map = unordered_map<int, vector<string>>();
    for (string word : words) {
        vector<string> wordList;
        if (map.find(word.length()) != map.end()) {
            wordList = map[word.length()];
        } else {
            wordList = vector<string>();
        }
        if (find(wordList.begin(), wordList.end(), word) == wordList.end()) {
            wordList.push_back(word);
        }
        map[word.length()] = wordList;
    }
    return map;
}

void solveForSingleWords(unordered_map<int, vector<string>> &wordList, unordered_map<int, vector<string>> &codeList, unordered_map<char, char> &codesExplain) {
    unordered_set<int> keySet = unordered_set<int>();
    for (auto &value : wordList) {
        keySet.insert(value.first);
    }
    for (int key : keySet) {
        vector<string> normalList = wordList[key];
        vector<string> encryptedList = codeList[key];
        if (normalList.size() == 1) {
            for (int i = 0; i < normalList.at(0).length(); i++) {
                codesExplain[encryptedList.at(0).at(i)] = normalList.at(0).at(i);
            }
            wordList.erase(key);
            codeList.erase(key);
        }
    }
}

vector<pair<int, int>> containsRepeatingLetters(string word) {
    vector<pair<int, int>> repeating = vector<pair<int, int>>();
    for (int i = 0; i < word.length(); i++) {
        for (int j = i + 1; j < word.length(); j++) {
            if (word.at(i) == word.at(j)) {
                repeating.emplace_back(i, j);
            }
        }
    }
    return repeating;
}

void solveForRepeatingLetters(unordered_map<int, vector<string>> &wordList, unordered_map<int, vector<string>> &codeList, unordered_map<char, char> &codesExplain) {
    for (auto &key : wordList) {
        vector<string> normalList = wordList[key.first];
        vector<string> encryptedList = codeList[key.first];
        for (string normalWord : normalList) {
            vector<pair<int, int>> normalPairs = containsRepeatingLetters(normalWord);
            if (normalPairs.size() > 0) {
                for (string encryptedWord : encryptedList) {
                    vector<pair<int, int>> encryptedPairs = containsRepeatingLetters(encryptedWord);
                    if (encryptedPairs == normalPairs) {
                        for (int i = 0; i < normalWord.length(); i++) {
                            codesExplain[encryptedWord.at(i)] = normalWord.at(i);
                        }
                    }
                }
            }
        }
    }
}

void print(vector<string> codes, unordered_map<char, char> codesExplain) {
    for (string code : codes) {
        for (char & m : code) {
            if (codesExplain.find(m) == codesExplain.end()) {
                cout << "*";
            } else {
                cout << codesExplain[m];
            }
        }
        cout << "  ";
    }
}

void removeFromCandidateList(vector<string> &candidateList, int index, char ch) {
    vector<string> removed = vector<string>();
    for (string word : candidateList) {
        if (word.at(index) != ch) {
            removed.push_back(word);
        }
    }
    for (auto & i : removed) {
        for (int j = 0; j < candidateList.size(); j++) {
            if (candidateList.at(j) == i) {
                candidateList.erase(candidateList.begin() + j);
                break;
            }
        }
    }
}

void solveForRemaining(unordered_map<int, vector<string>> &wordList, unordered_map<int, vector<string>> &codeList, unordered_map<char, char> &codesExplain) {
    for (auto &key : wordList) {
        vector<string> encryptedList = codeList[key.first];
        for (string encryptedWord : encryptedList) {
            vector<string> candidateList = (vector<string>) wordList[key.first]; //clone
            for (int i = 0; i < encryptedWord.length(); i++) {
                if (codesExplain.find(encryptedWord.at(i)) != codesExplain.end()) {
                    removeFromCandidateList(candidateList, i, codesExplain[encryptedWord.at(i)]);
                }
            }
            if (candidateList.size() == 1) {
                for (int i = 0; i < encryptedWord.length(); i++) {
                    codesExplain[encryptedWord.at(i)] = candidateList.at(0).at(i);
                }
            }
        }
    }
}

int main() {
    fstream file;
    file.open("Crypt.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int wordCount;
        string word, codeLine;
        vector<string> words = vector<string>();
        vector<string> codes;
        file >> wordCount;
        for (int i = 0; i < wordCount; i++) {
            file >> word;
            words.push_back(word);
        }
        while (!file.eof()) {
            getline(file, codeLine);
            getline(file, codeLine);
            codes = vector<string>();
            stringstream check(codeLine);
            string intermediate;
            while (getline(check, intermediate, ' ')) {
                codes.push_back(intermediate);
            }
            unordered_map<int, vector<string>> wordList = createWordLists(words);
            unordered_map<int, vector<string>> codeList = createWordLists(codes);
            unordered_map<char, char> codesExplain = unordered_map<char, char>();
            solveForSingleWords(wordList, codeList, codesExplain);
            solveForRepeatingLetters(wordList, codeList, codesExplain);
            solveForRemaining(wordList, codeList, codesExplain);
            print(codes, codesExplain);
            cout << "" << endl;
        }
    }
}