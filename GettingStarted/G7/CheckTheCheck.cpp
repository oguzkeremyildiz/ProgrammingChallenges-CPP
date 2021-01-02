//
// Created by Oğuz Kerem Yıldız on 2.01.2021.
//

#include <iostream>
#include <fstream>

using namespace std;

void blackKnight(char **board, int number1, int number2, int board1, int board2) {
    if (board[number1][number2] == 'n') {
        if (number1 - 2 >= 0 && number2 + 1 < board2) {
            if (board[number1 - 2][number2 + 1] == 'K') {
                cout << "white king is in check" << endl;
            }
        }
        if (number1 - 2 >= 0 && number2 - 1 >= 0) {
            if (board[number1 - 2][number2 - 1] == 'K') {
                cout << "white king is in check" << endl;
            }
        }
        if (number1 - 1 >= 0 && number2 - 2 >= 0) {
            if (board[number1 - 1][number2 - 2] == 'K') {
                cout << "white king is in check" << endl;
            }
        }
        if (number1 - 1 >= 0 && number2 + 2 < board2) {
            if (board[number1 - 1][number2 + 2] == 'K') {
                cout << "white king is in check" << endl;
            }
        }
        if (number1 + 1 < board1 && number2 + 2 < board2) {
            if (board[number1 + 1][number2 + 2] == 'K') {
                cout << "white king is in check" << endl;
            }
        }
        if (number1 + 1 < board1 && number2 + 2 < board2) {
            if (board[number1 + 1][number2 + 2] == 'K') {
                cout << "white king is in check" << endl;
            }
        }
        if (number1 + 2 < board1 && number2 - 1 >= 0) {
            if (board[number1 + 2][number2 - 1] == 'K') {
                cout << "white king is in check" << endl;
            }
        }
        if (number1 + 1 < board1 && number2 - 2 >= 0) {
            if (board[number1 + 1][number2 - 2] == 'K') {
                cout << "white king is in check" << endl;
            }
        }
    }
}

void whiteKnight(char **board, int number1, int number2, int board1, int board2) {
    if (board[number1][number2] == 'N') {
        if (number1 - 2 >= 0 && number2 + 1 < board2) {
            if (board[number1 - 2][number2 + 1] == 'k') {
                cout << "black king is in check" << endl;
            }
        }
        if (number1 - 2 >= 0 && number2 - 1 >= 0) {
            if (board[number1 - 2][number2 - 1] == 'k') {
                cout << "black king is in check" << endl;
            }
        }
        if (number1 - 1 >= 0 && number2 - 2 >= 0) {
            if (board[number1 - 1][number2 - 2] == 'k') {
                cout << "black king is in check" << endl;
            }
        }
        if (number1 - 1 >= 0 && number2 + 2 < board2) {
            if (board[number1 - 1][number2 + 2] == 'k') {
                cout << "black king is in check" << endl;
            }
        }
        if (number1 + 1 < board1 && number2 + 2 < board2) {
            if (board[number1 + 1][number2 + 2] == 'k') {
                cout << "black king is in check" << endl;
            }
        }
        if (number1 + 1 < board1 && number2 + 2 < board2) {
            if (board[number1 + 1][number2 + 2] == 'k') {
                cout << "black king is in check" << endl;
            }
        }
        if (number1 + 2 < board1 && number2 - 1 >= 0) {
            if (board[number1 + 2][number2 - 1] == 'k') {
                cout << "black king is in check" << endl;
            }
        }
        if (number1 + 1 < board1 && number2 - 2 >= 0) {
            if (board[number1 + 1][number2 - 2] == 'k') {
                cout << "black king is in check" << endl;
            }
        }
    }
}

void blackPawn(char **board, int number1, int number2, int board2) {
    if (board[number1][number2] == 'p') {
        if (number1 - 1 > 0 && number2 - 1 > 0) {
            if (board[number1 - 1][number2 - 1] == 'K') {
                cout << "white king is in check" << endl;
            }
        }
        if (number1 - 1 > 0 && number2 + 1 < board2) {
            if (board[number1 - 1][number2 + 1] == 'K') {
                cout << "white king is in check" << endl;
            }
        }
    }
}

void whitePawn(char **board, int number1, int number2, int board2) {
    if (board[number1][number2] == 'P') {
        if (number1 - 1 > 0 && number2 - 1 > 0) {
            if (board[number1 - 1][number2 - 1] == 'k') {
                cout << "black king is in check" << endl;
            }
        }
        if (number1 - 1 > 0 && number2 + 1 < board2) {
            if (board[number1 - 1][number2 + 1] == 'k') {
                cout << "black king is in check" << endl;
            }
        }
    }
}

void blackQueen(char **board, int number1, int number2, int board1, int board2) {
    if (board[number1][number2] == 'q') {
        int k = 1;
        while (number2 + k < board2) {
            if (board[number1][number2 + k] == '.') {
                k++;
            } else {
                if (board[number1][number2 + k] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
        int t = 1;
        while (number1 + t < board1) {
            if (board[number1 + t][number2] == '.'){
                t++;
            } else {
                if (board[number1 + t][number2] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
        k = 1;
        while (number2 - k >= 0) {
            if (board[number1][number2 - k] == '.') {
                k++;
            } else {
                if (board[number1][number2 - k] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        while (number1 - t >= 0) {
            if (board[number1 - t][number2] == '.') {
                t++;
            } else {
                if (board[number1 - t][number2] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        k = 1;
        while (number1 + t < board1 && number2 + k < board2) {
            if (board[number1 + t][number2 + k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 + t][number2 + k] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        k = 1;
        while (number1 - t >= 0 && number2 + k < board2) {
            if (board[number1 - t][number2 + k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 - t][number2 + k] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        k = 1;
        while (number1 - t >= 0 && number2 - k >= 0) {
            if (board[number1 - t][number2 - k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 - t][number2 - k] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        k = 1;
        while (number1 + t < board1 && number2 - k >= 0) {
            if (board[number1 + t][number2 - k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 + t][number2 - k] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
    }
}

void whiteQueen(char **board, int number1, int number2, int board1, int board2) {
    if (board[number1][number2] == 'Q') {
        int k = 1;
        while (number2 + k < board2) {
            if (board[number1][number2 + k] == '.') {
                k++;
            } else {
                if (board[number1][number2 + k] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
        int t = 1;
        while (number1 + t < board1) {
            if (board[number1 + t][number2] == '.') {
                t++;
            } else {
                if (board[number1 + t][number2] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
        k = 1;
        while (number2 - k >= 0) {
            if (board[number1][number2 - k] == '.') {
                k++;
            } else {
                if (board[number1][number2 - k] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        while (number1 - t >= 0) {
            if (board[number1 - t][number2] == '.') {
                t++;
            } else {
                if (board[number1 - t][number2] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        k = 1;
        while (number1 + t < board1 && number2 + k < board2) {
            if (board[number1 + t][number2 + k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 + t][number2 + k] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        k = 1;
        while (number1 - t >= 0 && number2 + k < board2) {
            if (board[number1 - t][number2 + k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 - t][number2 + k] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        k = 1;
        while (number1 - t >= 0 && number2 - k >= 0) {
            if (board[number1 - t][number2 - k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 - t][number2 - k] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        k = 1;
        while (number1 + t < board1 && number2 - k >= 0) {
            if (board[number1 + t][number2 - k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 + t][number2 - k] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
    }
}

void blackRook(char **board, int number1, int number2, int board1, int board2) {
    if (board[number1][number2] == 'r') {
        int x = 1;
        while (number2 + x < board2) {
            if (board[number1][number2 + x] == '.') {
                x++;
            } else {
                if (board[number1][number2 + x] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
    }
    if (board[number1][number2] == 'r') {
        int y = 1;
        while (number1 + y < board1) {
            if (board[number1 + y][number2] == '.') {
                y++;
            } else {
                if (board[number1 + y][number2] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
    }
    if (board[number1][number2] == 'r') {
        int k = 1;
        while (number2 - k >= 0) {
            if (board[number1][number2 - k] == '.') {
                k++;
            } else {
                if (board[number1][number2 - k] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
    }
    if (board[number1][number2] == 'r') {
        int t = 1;
        while (number1 - t >= 0) {
            if (board[number1 - t][number2] == '.') {
                t++;
            } else {
                if (board[number1 - t][number2] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
    }
}

void whiteRook(char **board, int number1, int number2, int board1, int board2) {
    if (board[number1][number2] == 'R') {
        int k = 1;
        while (number2 + k < board2) {
            if (board[number1][number2 + k] == '.') {
                k++;
            } else {
                if (board[number1][number2 + k] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
    }
    if (board[number1][number2] == 'R') {
        int t = 1;
        while (number1 + t < board1) {
            if (board[number1 + t][number2] == '.') {
                t++;
            } else {
                if (board[number1 + t][number2] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
    }
    if (board[number1][number2] == 'R') {
        int k = 1;
        while (number2 - k >= 0) {
            if (board[number1][number2 - k] == '.') {
                k++;
            } else {
                if (board[number1][number2 - k] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
    }
    if (board[number1][number2] == 'R') {
        int t = 1;
        while (number1 - t >= 0){
            if (board[number1 - t][number2] == '.') {
                t++;
            } else {
                if (board[number1 - t][number2] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
    }
}

void whiteBishop(char **board, int number1, int number2, int board1, int board2) {
    if (board[number1][number2] == 'B') {
        int t = 1;
        int k = 1;
        while (number1 + t < board1 && number2 + k < board2) {
            if (board[number1 + t][number2 + k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 + t][number2 + k] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        k = 1;
        while (number1 - t >= 0 && number2 + k < board2) {
            if (board[number1 - t][number2 + k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 - t][number2 + k] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        k = 1;
        while (number1 - t >= 0 && number2 - k >= 0) {
            if (board[number1 - t][number2 - k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 - t][number2 - k] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        k = 1;
        while (number1 + t < board1 && number2 - k >= 0) {
            if (board[number1 + t][number2 - k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 + t][number2 - k] == 'k') {
                    cout << "black king is in check" << endl;
                }
                break;
            }
        }
    }
}

void blackBishop(char **board, int number1, int number2, int board1, int board2) {
    if (board[number1][number2] == 'b') {
        int t = 1;
        int k = 1;
        while (number1 + t < board1 && number2 + k < board2) {
            if (board[number1 + t][number2 + k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 + t][number2 + k] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        k = 1;
        while (number1 - t >= 0 && number2 + k < board2) {
            if (board[number1 - t][number2 + k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 - t][number2 + k] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        k = 1;
        while (number1 - t >= 0 && number2 - k >= 0) {
            if (board[number1 - t][number2 - k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 - t][number2 - k] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
        t = 1;
        k = 1;
        while (number1 + t < board1 && number2 - k >= 0) {
            if (board[number1 + t][number2 - k] == '.') {
                t++;
                k++;
            } else {
                if (board[number1 + t][number2 - k] == 'K') {
                    cout << "white king is in check" << endl;
                }
                break;
            }
        }
    }
}

int main() {
    fstream file;
    file.open("Chess.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int count = 0;
        while (true) {
            int board1, board2;
            file >> board1;
            file >> board2;
            if (board1 == 0 && board2 == 0) {
                break;
            }
            char **board;
            board = (char **)malloc(board1 * sizeof(char *));
            for (int i = 0; i < board1; i++) {
                board[i] = (char *) malloc(board2 * sizeof(char));
            }
            for (int i = 0; i < board1; i++) {
                string line;
                file >> line;
                for (int j = 0; j < board2; j++) {
                    board[i][j] = line.at(j);
                }
            }
            for (int z = 0; z < board1; z++) {
                for (int t = 0; t < board2; t++) {
                    whiteBishop(board, z, t, board1, board2);
                    blackBishop(board, z, t, board1, board2);
                    whiteRook(board, z, t, board1, board2);
                    blackRook(board, z, t, board1, board2);
                    whiteQueen(board, z, t, board1, board2);
                    blackQueen(board, z, t, board1, board2);
                    whitePawn(board, z, t, board2);
                    blackPawn(board, z, t, board2);
                    whiteKnight(board, z, t, board1, board2);
                    blackKnight(board, z, t, board1, board2);
                }
            }
            count++;
            cout << count << endl;
        }
    }
}