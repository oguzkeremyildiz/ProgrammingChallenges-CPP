//
// Created by Oğuz Kerem Yıldız on 17.01.2021.
//

#ifndef COOKIES_CPP_BIGINTEGER_H
#define COOKIES_CPP_BIGINTEGER_H
#include <iostream>
#include <utility>
#include <string>
// working phase...

using namespace std;

class BigInteger {
private:
    string number;
public:
    BigInteger();
    BigInteger(string num);
    BigInteger(int num);
    void add(string num);
    void eject(string num);
    void multiply(string num);
    string value();
    bool operator ==(BigInteger b);
    bool operator !=(BigInteger b);
    void operator +=(string num);
    void operator *=(string num);
    bool operator >(BigInteger b);
    bool operator <(BigInteger b);
    void operator -=(string num);
    bool operator >=(BigInteger b);
    void operator =(BigInteger b);
};

BigInteger::BigInteger() {
    number = "0";
}

BigInteger::BigInteger(string num) {
    this->number = move(num);
}

BigInteger::BigInteger(int num) {
    this->number = to_string(num);
}

void BigInteger::add(string num) {
    string newString = "";
    string remaining = "0";
    for (int i = 0; i < max(num.length(), number.length()); ++i) {
        string first = "", second = "";
        int x = num.length();
        if (x - i - 1 > -1) {
            first.push_back(num.at(num.length() - i - 1));
        } else {
            first = "0";
        }
        x = number.length();
        if (x - i - 1 > -1) {
            second.push_back(number.at(number.length() - i - 1));
        } else {
            second = "0";
        }
        string current = to_string(stoi(first) + stoi(second) + stoi(remaining));
        if (current.length() > 1) {
            remaining = current.at(0);
            newString = current.at(1) + newString;
        } else {
            remaining = "0";
            newString = current.at(0) + newString;
        }
    }
    if (remaining != "0") {
        newString = remaining + newString;
    }
    this->number = move(newString);
}

void BigInteger::eject(string num) {
    string newString = "";
    if (number.length() > num.length() || number.length() == num.length() && number.at(0) > num.at(0)) {
        for (int i = 0; i < number.length(); ++i) {
            string first = "", second = "";
            int x = num.length();
            if (x - i - 1 > -1) {
                first.push_back(num.at(num.length() - i - 1));
            } else {
                first = "0";
            }
            second.push_back(number.at(number.length() - i - 1));
            if (stoi(second) < stoi(first)) {
                int currentIndex = number.length() - i - 2;
                while (number.at(currentIndex) == '0') {
                    number.at(currentIndex) = '9';
                    currentIndex--;
                }
                string s(1, number.at(currentIndex));
                number.at(currentIndex) = to_string(stoi(s) - 1).at(0);
                string st;
                st.push_back('1');
                st.push_back( + number.at(number.length() - i - 1));
                newString = to_string(stoi(st) - stoi(first)) + newString;
            } else {
                newString = to_string(stoi(second) - stoi(first)) + newString;
            }
        }
        while (newString.at(0) == '0') {
            newString.erase(newString.begin() + 0);
        }
        this->number = move(newString);
    } else {
        string temp = number;
        number = num;
        this->eject(temp);
        this->number = "-" + number;
    }
}

void BigInteger::multiply(string num) {
    string newString, remaining, numberT = number;
    int t = 0;
    for (int i = num.length() - 1; i > -1; i--) {
        string oldString = newString;
        remaining = "0";
        newString = "";
        for (int j = numberT.length() - 1; j > -1; j--) {
            string first, second;
            first.push_back(num.at(i));
            second.push_back(numberT.at(j));
            string current = to_string(stoi(first) * stoi(second) + stoi(remaining));
            if (current.length() > 1) {
                remaining = current.at(0);
                newString = current.at(1) + newString;
            } else {
                remaining = "0";
                newString = current.at(0) + newString;
            }
        }
        if (remaining != "0") {
            newString = remaining + newString;
        }
        string s = "";
        for (int j = 0; j < t; ++j) {
            s += "0";
        }
        newString = newString + s;
        if (oldString != "") {
            number = oldString;
            add(newString);
            newString = number;
        }
        t++;
    }
    this->number = newString;
}

string BigInteger::value() {
    return number;
}

void BigInteger::operator +=(string num) {
    add(num);
}

bool BigInteger::operator >(BigInteger b) {
    if (number.at(0) == '-' && b.number.at(0) == '-') {
        if (number.length() < b.number.length()) {
            return true;
        } else if (number.length() > b.number.length()) {
            return false;
        } else {
            for (int i = 1; i < number.length(); ++i) {
                if (number.at(i) < b.number.at(i)) {
                    return true;
                } else if (number.at(i) > b.number.at(i)) {
                    return false;
                }
            }
        }
        return false;
    } else if (number.at(0) == '-') {
        return false;
    } else if (b.number.at(0) == '-') {
        return true;
    }
    if (number.length() > b.number.length()) {
        return true;
    } else if (number.length() < b.number.length()) {
        return false;
    } else {
        for (int i = 0; i < number.length(); ++i) {
            if (number.at(i) > b.number.at(i)) {
                return true;
            } else if (number.at(i) < b.number.at(i)) {
                return false;
            }
        }
    }
    return false;
}

void BigInteger::operator -=(string num) {
    eject(num);
}

bool BigInteger::operator <(BigInteger b) {
    if (number.at(0) == '-' && b.number.at(0) == '-') {
        if (number.length() > b.number.length()) {
            return true;
        } else if (number.length() < b.number.length()) {
            return false;
        } else {
            for (int i = 1; i < number.length(); ++i) {
                if (number.at(i) > b.number.at(i)) {
                    return true;
                } else if (number.at(i) < b.number.at(i)) {
                    return false;
                }
            }
        }
        return false;
    } else if (number.at(0) == '-') {
        return true;
    } else if (b.number.at(0) == '-') {
        return false;
    }
    if (number.length() < b.number.length()) {
        return true;
    } else if (number.length() > b.number.length()) {
        return false;
    } else {
        for (int i = 0; i < number.length(); ++i) {
            if (number.at(i) < b.number.at(i)) {
                return true;
            } else if (number.at(i) > b.number.at(i)) {
                return false;
            }
        }
    }
    return false;
}

bool BigInteger::operator ==(BigInteger b) {
    if (number.length() > b.number.length()) {
        return false;
    } else if (number.length() < b.number.length()) {
        return false;
    }
    for (int i = 0; i < number.length(); ++i) {
        if (number.at(i) != b.number.at(i)) {
            return false;
        }
    }
    return true;
}

bool BigInteger::operator >=(BigInteger b) {
    return this->operator >(b) || this->operator ==(b);
}

void BigInteger::operator *=(string num) {
    multiply(num);
}

void BigInteger::operator =(BigInteger b) {
    this->number = b.value();
}

bool BigInteger::operator !=(BigInteger b) {
    return !this->operator==(b);
}

#endif //COOKIES_CPP_BIGINTEGER_H
