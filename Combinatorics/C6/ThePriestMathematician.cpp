//
// Created by Oğuz Kerem Yıldız on 18.01.2021.
//
#include <fstream>
#include <Util/BigInteger.h>

using namespace std;

int main() {
    fstream file;
    file.open("Priest.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        BigInteger f[10010];
        f[0] = BigInteger("0");
        int k = 1, cnt = 0;
        BigInteger d = BigInteger("1");
        for (int i = 1; i <= 10000; i ++) {
            f[i] = f[i - 1];
            f[i] += d.value();
            cnt++;
            if (cnt == k) {
                cnt = 0;
                k++;
                d *= "2";
            }
        }
        while (!file.eof()) {
            int n;
            file >> n;
            cout << f[n].value() << endl;
        }
    }
}