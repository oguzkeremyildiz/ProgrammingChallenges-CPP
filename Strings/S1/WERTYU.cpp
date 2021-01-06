//
// Created by Oğuz Kerem Yıldız on 6.01.2021.
//
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    fstream file;
    file.open("Keyboard.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        string strings;
        char characters[100];
        char keyboard[] = {'\'', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\\', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/'};
        while (!file.eof()) {
            file >> strings;
            strcpy(characters, strings.c_str());
            for (int i = 0; i < strings.size(); i++) {
                for (int j = 0; j < 47; j++) {
                    if (characters[i] == keyboard[j]) {
                        cout << keyboard[j - 1];
                    }
                }
            }
            cout << " ";
        }
    }
}