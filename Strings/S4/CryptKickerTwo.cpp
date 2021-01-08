//
// Created by Oğuz Kerem Yıldız on 8.01.2021.
//
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

void print(vector<string> &codes, unordered_map<char, char> &convert) {
    for (string code : codes) {
        for (int j = 0; j < code.length(); j++) {
            cout << convert.at(code.at(j));
        }
        cout << " ";
    }
}

bool isSuitable(vector<string> &currentCodes, vector<string> &words) {
    bool boolean = false;
    unordered_set<char> codesHash = unordered_set<char>();
    unordered_set<int> codesNumber = unordered_set<int>();
    unordered_set<char> wordsHash = unordered_set<char>();
    unordered_set<int> wordsNumber = unordered_set<int>();
    vector<int> codesList = vector<int>();
    vector<int> wordsList = vector<int>();
    unordered_set<char> codesTemporary = unordered_set<char>();
    unordered_set<char> wordsTemporary = unordered_set<char>();
    for (int i = 0; i < currentCodes.size(); i++) {
        for (int j = 0; j < currentCodes.at(i).length(); j++) {
            if (wordsTemporary.find(words.at(i).at(j)) == wordsTemporary.end()) {
                wordsNumber.insert(j);
            }
            if (codesTemporary.find(currentCodes.at(i).at(j)) == codesTemporary.end()) {
                codesNumber.insert(j);
            }
            wordsHash.insert(words.at(i).at(j));
            codesHash.insert(currentCodes.at(i).at(j));
            codesTemporary.insert(currentCodes.at(i).at(j));
            wordsTemporary.insert(words.at(i).at(j));
        }
        codesTemporary.clear();
        wordsTemporary.clear();
        codesList.insert(codesList.end(), codesNumber.begin(), codesNumber.end());
        wordsList.insert(wordsList.end(), wordsNumber.begin(), wordsNumber.end());
        codesNumber.clear();
        wordsNumber.clear();
    }
    if (wordsHash.size() == codesHash.size()) {
        boolean = true;
        if (codesList.size() == wordsList.size()) {
            for (int t = 0; t < codesList.size(); t++) {
                if (codesList.at(t) != wordsList.at(t)) {
                    boolean = false;
                    break;
                }
            }
        } else {
            boolean = false;
        }
    }
    return boolean;
}

void findCharacter(vector<string> &words, vector<string> &codes, unordered_map<char, char> &convert) {
    int j = 0;
    int start = 0;
    int m = 0;
    vector<string> currentCodes = vector<string>();
    for (int i = 0; i < codes.size(); i++){
        if (j == words.size()){
            if (isSuitable(currentCodes, words)) {
                break;
            } else {
                j = 0;
            }
        }
        if (words.at(j).length() == codes.at(i).length()) {
            j++;
            if (j == 1) {
                start = i;
            }
            currentCodes.push_back(codes.at(i));
        } else {
            j = 0;
            currentCodes.clear();
            if (words.at(j).length() == codes.at(i).length()) {
                j++;
                if (j == 1){
                    start = i;
                }
                currentCodes.push_back(codes.at(i));
            }
        }
    }
    for (int t = start; t < codes.size(); t++) {
        if (m == 9) {
            break;
        }
        for (int n = 0; n < codes.at(t).length(); n++) {
            if (convert.find(codes.at(t).at(n)) == convert.end()) {
                convert[codes.at(t).at(n)] = words.at(m).at(n);
            }
        }
        m++;
    }
}

int main() {
    fstream file;
    file.open("CryptTwo.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        string code;
        vector<string> words = vector<string>();
        vector<string> codes = vector<string>();
        unordered_map<char, char> convert = unordered_map<char, char>();
        words.emplace_back("the");
        words.emplace_back("quick");
        words.emplace_back("brown");
        words.emplace_back("fox");
        words.emplace_back("jumps");
        words.emplace_back("over");
        words.emplace_back("the");
        words.emplace_back("lazy");
        words.emplace_back("dog");
        while (!file.eof()) {
            file >> code;
            codes.emplace_back(code);
        }
        findCharacter(words, codes, convert);
        print(codes, convert);
    }
}
