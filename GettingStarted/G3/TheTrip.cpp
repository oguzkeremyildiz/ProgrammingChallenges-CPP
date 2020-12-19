//
// Created by Oğuz Kerem Yıldız on 19.12.2020.
//
#include <iostream>
#include <vector>

using namespace std;

void moneyTransfer(vector<int> moneys) {
    double transfer = 0;
    int total = 0;
    for (int money : moneys) {
        total += money;
    }
    total = total / moneys.size();
    for (int & money : moneys) {
        if (money < total) {
            transfer += total - money;
        } else if (money > total) {
            money = total;
        }
    }
    printf("%s%f\n", "$", transfer / 100.00);
    moneys.clear();
}

int main() {
    vector<int> moneys;
    printf("%s\n", "Enter the number of people:");
    int number;
    cin >> number;
    printf("%s\n", "Enter the moneys:");
    for (int i = 0; i < number; i++) {
        double d;
        cin >> d;
        moneys.push_back((int) (d * 100));
    }
    moneyTransfer(moneys);
    moneys.clear();
    while (number != 0) {
        printf("%s\n", "Enter the number of people:");
        int number;
        cin >> number;
        if (number != 0) {
            printf("%s\n", "Enter the moneys:");
            for (int i = 0; i < number; i++) {
                double d;
                cin >> d;
                moneys.push_back((int) (d * 100));
            }
            moneyTransfer(moneys);
        }
    }
}
